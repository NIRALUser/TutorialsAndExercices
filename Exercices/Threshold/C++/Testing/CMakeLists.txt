# Test on the output for a given threshold
set(Data Data) 

set(TEMP_DIR ${Threshold_BINARY_DIR}/Testing/Temporary )
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${Data} )

set(Output1 ${SOURCE_DIR}/outputT2-30.nrrd )
set(Output2 ${SOURCE_DIR}/outputT2-200.nrrd )
set(OutputTrash ${SOURCE_DIR}/outputThrash.nrrd )
set(Input ${SOURCE_DIR}/inputT2.nrrd )
include_directories( ${CMAKE_SOURCE_DIR} )
add_executable(ThresholdTest ThresholdTest.cxx)
target_link_libraries(ThresholdTest ThresholdLib)
set( ThresholdTestResult ${TEMP_DIR}/output.nrrd )

# Test checking that the program cannot run without arguments
set(OpenFile OpenFileTest)
add_test(NAME ${OpenFile} COMMAND $<TARGET_FILE:Threshold>)
set_tests_properties( ${OpenFile} PROPERTIES WILL_FAIL true )

# Test checking that the threshold value cannot go above 255
add_test(NAME ThresholdLimitMaxTest COMMAND $<TARGET_FILE:Threshold>
  ${Input}
  ${OutputTrash}
  -t 260
)
set_tests_properties( ThresholdLimitMaxTest PROPERTIES WILL_FAIL true )
 
# Test checking that the threshold value cannot go below 0
add_test(NAME ThresholdLimitMinTest COMMAND $<TARGET_FILE:Threshold>
  ${Input}
  ${OutputTrash}
  -t -10
)
set_tests_properties( ThresholdLimitMinTest PROPERTIES WILL_FAIL true )

#Test checking that a wrong input will prevent the program from running
add_test(NAME WrongInputTest COMMAND $<TARGET_FILE:Threshold>
  WrongInput.nrrd
  ${OutputTrash}
  -t 20
)
set_tests_properties( WrongInputTest PROPERTIES WILL_FAIL true )

# Tests checking that that the output image is what is expected

add_test(NAME ThresholdTest COMMAND $<TARGET_FILE:ThresholdTest>
  --compare
    ${ThresholdTestResult}
    ${Output1}
  ModuleEntryPoint
    ${Input}
    ${ThresholdTestResult}
    -t 30
  )

add_test(NAME ThresholdTest2 COMMAND $<TARGET_FILE:ThresholdTest>
  --compare
    ${ThresholdTestResult}
    ${Output2}
  ModuleEntryPoint
    ${Input}
    ${ThresholdTestResult}
    -t 200
  )

# Test for the command --help
add_test(NAME PrintHelp COMMAND $<TARGET_FILE:Threshold> --help)
