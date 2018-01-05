# Required Vars:
# ${LIB_NAME}
# ${LIB_PUBLIC_HEADERS}

SET(INSTALL_INCDIR include)
SET(INSTALL_BINDIR bin)
IF(WIN32)
    SET(INSTALL_LIBDIR bin)
    SET(INSTALL_ARCHIVEDIR lib)
ELSE(WIN32)
    SET(INSTALL_LIBDIR lib${LIB_POSTFIX})
    SET(INSTALL_ARCHIVEDIR lib${LIB_POSTFIX})
ENDIF(WIN32)


IF(NOT USE_CUSTOM_SOURCE_GROUPS)

    SET(HEADERS_GROUP "Headers")

    SOURCE_GROUP(
        ${HEADERS_GROUP}
        FILES ${LIB_PUBLIC_HEADERS}
    )
		
ENDIF()

#source_group("Shaders"        FILES ${TARGET_GLSL} )
source_group("Template Files" FILES ${TARGET_IN} )

INSTALL(
    TARGETS ${LIB_NAME}
    RUNTIME DESTINATION ${INSTALL_BINDIR}
    LIBRARY DESTINATION ${INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR}
)


IF(NOT GWEARTH_BUILD_FRAMEWORKS)
    INSTALL(
        FILES        ${LIB_PUBLIC_HEADERS}
        DESTINATION ${INSTALL_INCDIR}/${LIB_NAME}
    )
ELSE()
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "${GWEARTH_BUILD_FRAMEWORKS_INSTALL_NAME_DIR}")
    
    SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES
         FRAMEWORK TRUE
         FRAMEWORK_VERSION ${OSGEARTH_MAJOR_VERSION}
         PUBLIC_HEADER  "${LIB_PUBLIC_HEADERS}"
         INSTALL_NAME_DIR "${GWEARTH_BUILD_FRAMEWORKS_INSTALL_NAME_DIR}"
    )
    # MESSAGE("${OSG_COMPILE_FRAMEWORKS_INSTALL_NAME_DIR}")
ENDIF()
