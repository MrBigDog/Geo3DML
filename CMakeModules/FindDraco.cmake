
#  DRACO_FOUND

#  DRACO_INCLUDE_DIR
#  DRACO_LIBRARY_DIR

#  DRACO_LIBRARIES


# $DRACO_DIR is an environment variable that would
# correspond to the ./configure --prefix=$DRACO_DIR

FIND_PATH( DRACO_DIR core/draco_version.h )
FIND_PATH( DRACO_INCLUDE_DIR core/draco_version.h ${DRACO_DIR} ) 

FIND_LIBRARY(DRACO_LIBRARY NAMES draco PATHS ${DRACO_LIBRARY_DIR})
FIND_LIBRARY(DRACO_LIBRARY_DEBUG NAMES draco PATHS ${DRACO_LIBRARY_DIR})

# SET( PHYSX3_LIBRARIES 
    # ${PHYSX3_LIBRARY}
    # ${PHYSX3_COMMON_LIBRARY}
    # ${PHYSX3_COOKING_LIBRARY}
    # ${PHYSX3_EXT_LIBRARY}
    # ${PHYSX3_VEHICLE_LIBRARY}
    # ${PHYSX3_TASK_LIBRARY}
    # ${PHYSX3_PVD_LIBRARY}
    # ${PHYSX3_ProfileSDK_LIBRARY}
    # )
    
SET( DRACO_FOUND "NO" )
IF( DRACO_INCLUDE_DIR)
    SET( DRACO_FOUND "YES" )
ENDIF( DRACO_INCLUDE_DIR )

