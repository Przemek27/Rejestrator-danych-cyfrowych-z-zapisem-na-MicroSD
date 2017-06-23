	component processor is
		port (
			clk_clk             : in  std_logic := 'X'; -- clk
			spi_0_external_MISO : in  std_logic := 'X'; -- MISO
			spi_0_external_MOSI : out std_logic;        -- MOSI
			spi_0_external_SCLK : out std_logic;        -- SCLK
			spi_0_external_SS_n : out std_logic         -- SS_n
		);
	end component processor;

	u0 : component processor
		port map (
			clk_clk             => CONNECTED_TO_clk_clk,             --            clk.clk
			spi_0_external_MISO => CONNECTED_TO_spi_0_external_MISO, -- spi_0_external.MISO
			spi_0_external_MOSI => CONNECTED_TO_spi_0_external_MOSI, --               .MOSI
			spi_0_external_SCLK => CONNECTED_TO_spi_0_external_SCLK, --               .SCLK
			spi_0_external_SS_n => CONNECTED_TO_spi_0_external_SS_n  --               .SS_n
		);

