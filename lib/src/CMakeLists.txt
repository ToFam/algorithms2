SET (HEADER_PATH ${algorithms2_SOURCE_DIR}/lib/include)
SET (TARGET_H
		${HEADER_PATH}/PriorityQueue.h
)

include_directories (${HEADER_PATH})
		
SET (TARGET_SRC
		PriorityQueue.cpp
)

add_library (algolib ${TARGET_H} ${TARGET_SRC})