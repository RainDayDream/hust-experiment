set origin_dir "."

create_project mips_cpu $origin_dir/mips_cpu -part xc7a100tcsg324-1

add_files -scan_for_includes $origin_dir/verilog
add_files -fileset constrs_1 -norecurse $origin_dir/xdc/LogisimToplevelShell.xdc

update_compile_order -fileset sources_1
update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

launch_runs impl_1 -to_step write_bitstream -jobs 4
