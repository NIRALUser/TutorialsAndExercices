set(Data Data) 

set(TEMP_DIR ${MedianFilter_BINARY_DIR}/Testing/Temporary )
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${Data} )

set(BaselineRadius2 ${SOURCE_DIR}/baselineT2Radius2.nrrd )
set(BaselineRadius4 ${SOURCE_DIR}/baselineT2Radius4.nrrd )
set(DummyOutput ${SOURCE_DIR}/DummyOutput.nrrd )
set(Input ${SOURCE_DIR}/inputT2.nrrd )
include_directories( ${CMAKE_SOURCE_DIR} )
add_executable(MedianFilterTest MedianFilterTest.cxx)
target_link_libraries(MedianFilterTest MedianFilterLib)
set( RadiusValue2 ${TEMP_DIR}/RadiusValue2.nrrd )
set( RadiusValue4 ${TEMP_DIR}/RadiusValue4.nrrd )

# Test checking that the program cannot run without arguments
add_test(NAME OpenFileTest COMMAND $<TARGET_FILE:MedianFilter>)
set_tests_properties(OpenFileTest PROPERTIES WILL_FAIL true )

# Test checking that the radius value cannot go below 1
add_test(NAME RadiusLimitMin COMMAND $<TARGET_FILE:MedianFilter>
  ${Input}
  ${DummyOutput}
  -r 0
)
set_tests_properties( RadiusLimitMin PROPERTIES WILL_FAIL true )

#Test checking that a wrong input will prevent the program from running
add_test(NAME MedianFilterWrongInputFileName COMMAND $<TARGET_FILE:MedianFilter>
  WrongInput.nrrd
  ${DummyOutput}
  -r 20
)
set_tests_properties( MedianFilterWrongInputFileName PROPERTIES WILL_FAIL true )

# Tests checking that that the output image is what is expected
add_test(NAME MedianFilterRadiusValue2 COMMAND $<TARGET_FILE:MedianFilterTest>
  --compare
    ${BaselineRadius2}
    ${RadiusValue2}
  ModuleEntryPoint
    ${Input}
    ${RadiusValue2}
    -r 2
  )

add_test(NAME MedianFilterRadiusValue4 COMMAND $<TARGET_FILE:MedianFilterTest>
  --compare
    ${BaselineRadius4}
    ${RadiusValue4}
  ModuleEntryPoint
    ${Input}
    ${RadiusValue4}
    -r 4
  )

# Test for the command --help
add_test(NAME PrintHelp COMMAND $<TARGET_FILE:MedianFilter> --help)
