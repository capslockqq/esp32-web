import argparse
import json
from pathlib import Path
import shutil
import os


def create_config(prj_name: str):
    config = {
        'Project name': prj_name,
        'version': '1.0.0',
        'Folder name': prj_name.replace(' ', '_').lower()
    }
    with open('config.json', 'w+', encoding='utf-8') as f:
        json.dump(config, f, ensure_ascii=False, indent=4)





def rename_template_file(file_location: str, template_filename: str, class_name: str, new_filename: str, rename_file: bool):
    path = f'{file_location}/{template_filename}'
    with open(path, 'r') as f:
        filedata = f.read()
    
    filedata = filedata.replace('ProjectName', class_name).replace('project_name', new_filename[:new_filename.find('.')])

    with open(path, 'w') as f:
        f.write(filedata)

    if rename_file:
        os.rename(path, f'{file_location}/{new_filename}')


def create_application_structure(prj_name: str):
    folder_name = prj_name.lower().replace(' ', '_')
    os.makedirs(f'{folder_name}/application_wrapper')
    shutil.copy('esp32_webserver/generate_project/application/application.cpp', f'{folder_name}/application_wrapper')
    shutil.copy('esp32_webserver/generate_project/application/application.hpp', f'{folder_name}/application_wrapper')

    os.makedirs(f'{folder_name}/application')
    shutil.copy('esp32_webserver/generate_project/application/project_name.hpp', f'{folder_name}/application')
    shutil.copy('esp32_webserver/generate_project/application/project_name.cpp', f'{folder_name}/application')

    class_name = prj_name.title().replace(' ', '')
    rename_template_file(f'{folder_name}/application', 'project_name.hpp', class_name, f'{folder_name}.hpp', True)
    rename_template_file(f'{folder_name}/application', 'project_name.cpp', class_name, f'{folder_name}.cpp', True)

    rename_template_file(f'{folder_name}/application_wrapper', 'application.hpp', class_name, f'{folder_name}.hpp', False)
    rename_template_file(f'{folder_name}/application_wrapper', 'application.cpp', class_name, f'{folder_name}.hpp', False)


def main():
    parser = argparse.ArgumentParser(description='Setup project script')
    parser.add_argument('-n', '--prj_name', help='Name of the project', required=True)
    args = parser.parse_args()
    create_config(args.prj_name)
    create_application_structure(args.prj_name)

if __name__ == "__main__":
    main()