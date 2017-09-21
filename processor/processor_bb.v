
module processor (
	clk_clk,
	input_data_export,
	spi_0_external_MISO,
	spi_0_external_MOSI,
	spi_0_external_SCLK,
	spi_0_external_SS_n,
	uart_0_external_rxd,
	uart_0_external_txd);	

	input		clk_clk;
	input	[7:0]	input_data_export;
	input		spi_0_external_MISO;
	output		spi_0_external_MOSI;
	output		spi_0_external_SCLK;
	output		spi_0_external_SS_n;
	input		uart_0_external_rxd;
	output		uart_0_external_txd;
endmodule
