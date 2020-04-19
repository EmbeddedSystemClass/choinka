library verilog;
use verilog.vl_types.all;
entity choin is
    port(
        PWM_OUT         : out    vl_logic;
        CLK             : in     vl_logic;
        SET             : in     vl_logic;
        DUTY            : in     vl_logic_vector(7 downto 0)
    );
end choin;
