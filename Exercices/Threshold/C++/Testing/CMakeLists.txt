# Test on the output for a given threshold
set(Data Data) 

set(TEMP_DIR ${Threshold_BINARY_DIR}/Testing/Temporary )
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${Data} )

set(Baseline1 ${SOURCE_DIR}/outputT2-30.nrrd )
set(Baseline2 ${SOURCE_DIR}/outputT2-200.nrrd )
set(DummyOutput ${SOURCE_DIR}/DummyOutput.nrrd )
set(Input ${SOURCE_DIR}/inputT2.nrrd )
include_directories( ${CMAKE_SOURCE_DIR} )
add_executable(ThresholdTest ThresholdTest.cxx)
target_link_libraries(ThresholdTest ThresholdLib)
set( ThresholdValue30 ${TEMP_DIR}/ThresholdValue30.nrrd )
set( ThresholdValue200 ${TEMP_DIR}/ThresholdValue200.nrrd )

# Test checking that the program cannot run without arguments
add_test(NAME OpenFileTest COMMAND $<TARGET_FILE:Threshold>)
set_tests_properties(OpenFileTest PROPERTIES WILL_FAIL true )

# Test checking that the threshold value cannot go above 255
add_test(NAME ThresholdLimitMax COMMAND $<TARGET_FILE:Threshold>
  ${Input}
  ${DummyOutput}
  -t 260
)
set_tests_properties( ThresholdLimitMax PROPERTIES WILL_FAIL true )
 
# Test checking that the threshold value cannot go below 0
add_test(NAME ThresholdLimitMin COMMAND $<TARGET_FILE:Threshold>
  ${Input}
  ${DummyOutput}
  -t -10
)
set_tests_properties( ThresholdLimitMin PROPERTIES WILL_FAIL true )

#Test checking that a wrong input will prevent the program from running
add_test(NAME ThresholdWrongInputFileName COMMAND $<TARGET_FILE:Threshold>
  WrongInput.nrrd
  ${DummyOutput}
  -t 20
)
set_tests_properties( ThresholdWrongInputFileName PROPERTIES WILL_FAIL true )

# Tests checking that that the output image is what is expected

add_test(NAME ThresholdValue30 COMMAND $<TARGET_FILE:ThresholdTest>
  --compare
    ${Baseline1}
    ${ThresholdValue30}
  ModuleEntryPoint
    ${Input}
    ${ThresholdValue30}
    -t 30
  )

add_test(NAME ThresholdValue200 COMMAND $<TARGET_FILE:ThresholdTest>
  --compare
    ${Baseline2}
    ${ThresholdValue200}
  ModuleEntryPoint
    ${Input}
    ${ThresholdValue200}
    -t 200
  )

# Test for the command --help
add_test(NAME PrintHelp COMMAND $<TARGET_FILE:Threshold> --help)
