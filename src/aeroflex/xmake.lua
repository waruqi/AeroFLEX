target("aeroflex")
    set_kind("binary")
    set_runargs({"-f"}, {"../../../../examples/rans/example.rans"}, {"-o"}, {"../../../../examples/rans/test.vtu"})
    add_deps("flexgui", "implot", "rans")
    add_packages("imgui", "eigen", "openmp")
    add_files("src/*.cpp")
    -- add_files("dev/*.cpp")
    add_includedirs("../common")
