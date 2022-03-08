pushd "%~dp0" 
set current_dir=%cd%
py.exe %current_dir%\create_factory.py
popd