SET (HEADER_PATH ${algorithms2_SOURCE_DIR}/lib/include)
SET (TARGET_H
		${HEADER_PATH}/PriorityQueue.h
		${HEADER_PATH}/BinaryHeap.h
		
		${HEADER_PATH}/Lib.h
)

include_directories (${HEADER_PATH})
		
SET (TARGET_SRC
		Lib.cpp
)

add_library (algolib ${TARGET_H} ${TARGET_SRC})