add_library(engine
    event_engine.cpp
    order_book.cpp
    exchange.cpp
    agent.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
