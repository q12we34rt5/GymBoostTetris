import ctypes

class State(ctypes.Structure):
    _fields_ = [
        ('board'         , ctypes.c_uint32 * 32),
        ('game_state'    , ctypes.c_bool       ),
        ('next'          , ctypes.c_int8   * 14),
        ('hold'          , ctypes.c_int8       ),
        ('has_holded'    , ctypes.c_bool       ),
        ('current'       , ctypes.c_int8       ),
        ('rot'           , ctypes.c_int8       ),
        ('x'             , ctypes.c_int32      ),
        ('y'             , ctypes.c_int32      ),
        ('clean_count'   , ctypes.c_int32      ),
        ('life_time'     , ctypes.c_int32      ),
        ('seed'          , ctypes.c_uint32     ),
        ('srs_index'     , ctypes.c_int32      )
    ]

class StateHQ(ctypes.Structure):
    _fields_ = [
        ('board'         , ctypes.c_uint8 * (32 * 18)),
        ('game_state'    , ctypes.c_bool       ),
        ('next'          , ctypes.c_int8   * 14),
        ('hold'          , ctypes.c_int8       ),
        ('has_holded'    , ctypes.c_bool       ),
        ('current'       , ctypes.c_int8       ),
        ('rot'           , ctypes.c_int8       ),
        ('x'             , ctypes.c_int32      ),
        ('y'             , ctypes.c_int32      ),
        ('clean_count'   , ctypes.c_int32      )
    ]

class FunctionTable(ctypes.Structure):
    _fields_ = [
        ('reset'        , ctypes.c_void_p),
        ('generateBlock', ctypes.c_void_p),
        ('moveLeft'     , ctypes.c_void_p),
        ('moveRight'    , ctypes.c_void_p),
        ('softDrop'     , ctypes.c_void_p),
        ('hardDrop'     , ctypes.c_void_p),
        ('rotateLeft'   , ctypes.c_void_p),
        ('rotateRight'  , ctypes.c_void_p),
        ('hold'         , ctypes.c_void_p),
        ('moveBlock'    , ctypes.c_void_p),
        ('toString'     , ctypes.c_void_p),
        ('eraseCurrent' , ctypes.c_void_p),
        ('pasteCurrent' , ctypes.c_void_p)
    ]
