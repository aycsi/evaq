add_library(engine
    event_engine.cpp
    order_book.cpp
    exchange.cpp
    market_e.cpp
    noise_ag.cpp
    informed_ag.cpp
    simulator.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
