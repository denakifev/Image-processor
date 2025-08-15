find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(VENV_DIR ${CMAKE_BINARY_DIR}/venv)
set(REQUIREMENTS_TXT ${CMAKE_SOURCE_DIR}/requirements.txt)

if(WIN32)
  set(PYTHON_EXECUTABLE ${VENV_DIR}/Scripts/python.exe)
  set(PIP_EXECUTABLE    ${VENV_DIR}/Scripts/pip.exe)
else()
  set(PYTHON_EXECUTABLE ${VENV_DIR}/bin/python)
  set(PIP_EXECUTABLE    ${VENV_DIR}/bin/pip)
endif()

add_custom_target(setup_py3_venv
  COMMAND ${Python3_EXECUTABLE} -m venv ${VENV_DIR}
  COMMAND ${PIP_EXECUTABLE} install --upgrade pip
  COMMAND ${PIP_EXECUTABLE} install -r ${REQUIREMENTS_TXT}
  COMMENT "Creating Python venv and installing requirements..."
)