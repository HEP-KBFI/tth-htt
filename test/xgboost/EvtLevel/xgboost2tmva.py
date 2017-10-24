import re
import xml.etree.cElementTree as ET

#from xml.etree.ElementTree import Element, SubElement
#from xml.etree import ElementTree 
from xml.dom import minidom

regex_float_pattern = r'[-+]?(\d+(\.\d*)?|\.\d+)([eE][-+]?\d+)?'
 
	
def build_tree(xgtree, base_xml_element, var_indices):
	#print (xgtree)
	parent_element_dict = {'0':base_xml_element}
	pos_dict = {'0':'s'}
	for line in xgtree.split('\n'):
		if not line: continue
		result1 = re.match(r'(\t*)(\d+):leaf=({0})$'.format(regex_float_pattern), line)
		result2 = re.match(r'(\t*)([0-9]+):\[f(?P<var>.+)<(?P<cut>{0})\]\syes=(?P<yes>\d+),no=(?P<no>\d+)'.format(regex_float_pattern),line)
		#if 1>0 : #':leaf=' in line:
		#	#leaf node
		if result1 is not None:
				depth = result1.group(1).count('\t')
				inode = result1.group(2)
				res = result1.group(3)
				#print (depth,int(inode),float(res),parent_element_dict,len(parent_element_dict))
				node_elementTree = ET.SubElement(parent_element_dict['0'], "Node", pos=str(pos_dict['0']),
                                             depth=str(depth), NCoef="0", IVar="-1", Cut="0.0e+00", 
											 cType="1", res=str(res), rms="0.0e+00", purity="0.0e+00", nType="-99")
		else :
			if result2 is not None:
				#\t\t3:[var_topcand_mass<138.19] yes=7,no=8,missing=7
				# 6:[f28<20.385] yes=13,no=14,missing=13
				#print (line)
				#print (result2)
				depth = result2.group(1).count('\t')
				inode = result2.group(2)
				var = result2.group('var')
				cut = result2.group('cut')
				#print (depth,int(inode),var,cut)
				#print (cut)
				#missing = result2.group('missing')
				lnode = result2.group('yes')
				rnode = result2.group('no')
				pos_dict[lnode] = 'l'
				pos_dict[rnode] = 'r'
				node_elementTree = ET.SubElement(parent_element_dict[inode], "Node", pos=str(pos_dict[inode]),
                                             depth=str(depth), NCoef="0", IVar=str(var_indices[int(var)]), Cut=str(cut),
                                             cType="1", res="0.0e+00", rms="0.0e+00", purity="0.0e+00", nType="0")
				parent_element_dict[lnode] = node_elementTree
				parent_element_dict[rnode] = node_elementTree
			else:
				#print line
				pass
				
def convert_model(model, input_variables, output_xml):
    NTrees = len(model) # len(model)
    var_list = input_variables
    var_indices = {}
     
    # <MethodSetup>
    MethodSetup = ET.Element("MethodSetup", Method="BDT::BDT")
 
    # <Variables>
    Variables = ET.SubElement(MethodSetup, "Variables", NVar=str(len(var_list)))
    for ind, val in enumerate(var_list):
		name = val #[0]
		var_type = val[1]
		#print ("var name",ind,name,var_type)
		var_indices[ind] = name
		Variable = ET.SubElement(Variables, "Variable", VarIndex=str(ind), Type=val[1], 
			Expression=name, Label=name, Title=name, Unit="", Internal=name, 
			Min="0.0e+00", Max="0.0e+00")
 
    # <GeneralInfo>
    GeneralInfo = ET.SubElement(MethodSetup, "GeneralInfo")
    Info_Creator = ET.SubElement(GeneralInfo, "Info", name="Creator", value="xgboost2TMVA")
    Info_AnalysisType = ET.SubElement(GeneralInfo, "Info", name="AnalysisType", value="Classification")
 
    # <Options>
    Options = ET.SubElement(MethodSetup, "Options")
    Option_NodePurityLimit = ET.SubElement(Options, "Option", name="NodePurityLimit", modified="No").text = "5.00e-01"
    Option_BoostType = ET.SubElement(Options, "Option", name="BoostType", modified="Yes").text = "Grad"
     
    # <Weights>
    Weights = ET.SubElement(MethodSetup, "Weights", NTrees=str(NTrees), AnalysisType="1")
     
    for itree in  range(NTrees):
        BinaryTree = ET.SubElement(Weights, "BinaryTree", type="DecisionTree", boostWeight="1.0e+00")
        build_tree(model[itree], BinaryTree, var_indices)
	tree = ET.ElementTree(MethodSetup)
	tree.write(output_xml, xml_declaration=True)
	#tree.write(prettify(output_xml)) 
	#print (len(model))
	#print (len(model))
    # format it with 'xmllint --format'
	