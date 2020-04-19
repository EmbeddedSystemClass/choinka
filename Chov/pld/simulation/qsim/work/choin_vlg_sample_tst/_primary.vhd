library verilog;
use verilog.vl_types.all;
entity choin_vlg_sample_tst is
    port(
        CLK             : in     vl_logic;
        DUTY            : in     vl_logic_vector(7 downto 0);
        SET             : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end choin_vlg_sample_tst;
