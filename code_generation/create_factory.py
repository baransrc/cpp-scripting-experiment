import os
import re

path = os.curdir + '/../scripting_layer/'
script_factory_cpp_path = path + 'ScriptFactory.cpp'
files_in_directory = os.listdir(path)

scripting_namespace = 'Gameplay::'
generated_includes = '#include \"scripting_pch.h\"\n' + '#include \"ScriptFactory.h\"\n' 
generated_body = scripting_namespace + 'Script* InstantiateScript(Gameplay::Entity* script_owner, const std::string& script_name)\n{'

for file_name in files_in_directory:
    if file_name[-2:] == '.h':
        header_file = open(path+file_name)
        header_file_as_string = header_file.read()
        header_file_as_string_without_spaces = re.sub(r"[\n\t\s]*", "", header_file_as_string)
        class_name = file_name[0:-2]
        is_script_file = header_file_as_string_without_spaces.find('class'+class_name+':publicScript') != -1

        if is_script_file:
            print("Found script header file: " + file_name)
            generated_includes += '#include \"' + file_name + '\"\n'
            generated_body += '\n\tif (script_name == \"' + class_name + '\")\n\t{\n\t\treturn new ' + scripting_namespace + class_name + '(script_owner);\n\t}\n'
            
generated_body += '}'

generated_body = generated_includes + '\n\n' + generated_body

open(script_factory_cpp_path, "w").write(generated_body)