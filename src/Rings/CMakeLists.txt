set(INTEGER_SRCS
    Integer.cc
)

add_library(IntegerLib ${INTEGER_SRCS})

target_link_libraries(IntegerLib gmpxx gmp)