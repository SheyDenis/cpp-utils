MACRO(SET_CMAKE_TARGET_PROPERTIES)
    CMAKE_PARSE_ARGUMENTS(TARGET_PROPERTIES
                          ""
                          "TARGET"
                          ""
                          ${ARGN}
    )
    IF (NOT DEFINED TARGET_PROPERTIES_TARGET)
        MESSAGE(FATAL_ERROR "SET_CMAKE_TARGET_PROPERTIES: No target provided.")
    ENDIF ()
    SET_TARGET_PROPERTIES(${TARGET_PROPERTIES_TARGET} PROPERTIES CXX_STANDARD 17 POSITION_INDEPENDENT_CODE ON)
ENDMACRO(SET_CMAKE_TARGET_PROPERTIES)
