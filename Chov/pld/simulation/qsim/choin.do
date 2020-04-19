onerror {quit -f}
vlib work
vlog -work work choin.vo
vlog -work work choin.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.choin_vlg_vec_tst
vcd file -direction choin.msim.vcd
vcd add -internal choin_vlg_vec_tst/*
vcd add -internal choin_vlg_vec_tst/i1/*
add wave /*
run -all
