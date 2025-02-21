-- target("rans-dev")
--     set_kind("binary")
--     add_packages("eigen", "openmp")
--     add_includedirs("../common")
--     add_includedirs("include", {public = true})
--     -- add_files("src/*.cpp")
--     add_files("dev/*.cpp")

target("rans")
    set_kind("static")
    add_packages("eigen", "openmp")
    add_includedirs("../common")
    add_includedirs("include", {public = true})