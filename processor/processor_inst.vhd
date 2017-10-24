	component processor is
		port (
			clk_clk                 : in  std_logic                    := 'X';             -- clk
			generator_output_export : out std_logic_vector(7 downto 0);                    -- export
			input_data_export       : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			spi_0_external_MISO     : in  std_logic                    := 'X';             -- MISO
			spi_0_external_MOSI     : out std_logic;                                       -- MOSI
			spi_0_external_SCLK     : out std_logic;                                       -- SCLK
			spi_0_external_SS_n     : out std_logic;                                       -- SS_n
			uart_0_external_rxd     : in  std_logic                    := 'X';             -- rxd
			uart_0_external_txd     : out std_logic                                        -- txd
		);
	end component processor;

	u0 : component processor
		port map (
			clk_clk                 => CONNECTED_TO_clk_clk,                 --              clk.clk
			generator_output_export => CONNECTED_TO_generator_output_export, -- generator_output.export
			input_data_export       => CONNECTED_TO_input_data_export,       --       input_data.export
			spi_0_external_MISO     => CONNECTED_TO_spi_0_external_MISO,     --   spi_0_external.MISO
			spi_0_external_MOSI     => CONNECTED_TO_spi_0_external_MOSI,     --                 .MOSI
			spi_0_external_SCLK     => CONNECTED_TO_spi_0_external_SCLK,     --                 .SCLK
			spi_0_external_SS_n     => CONNECTED_TO_spi_0_external_SS_n,     --                 .SS_n
			uart_0_external_rxd     => CONNECTED_TO_uart_0_external_rxd,     --  uart_0_external.rxd
			uart_0_external_txd     => CONNECTED_TO_uart_0_external_txd      --                 .txd
		);

