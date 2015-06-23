//////////////////////////////////////////////////////////////////////
////                                                              ////
////  spi_shift.v                                                 ////
////                                                              ////
////  This file is part of the SPI IP core project                ////
////  http://www.opencores.org/projects/spi/                      ////
////                                                              ////
////  Author(s):                                                  ////
////      - Simon Srot (simons@opencores.org)                     ////
////                                                              ////
////  All additional information is avaliable in the Readme.txt   ////
////  file.                                                       ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
////                                                              ////
//// Copyright (C) 2002 Authors                                   ////
////                                                              ////
//// This source file may be used and distributed without         ////
//// restriction provided that this copyright statement is not    ////
//// removed from the file and that any derivative work contains  ////
//// the original copyright notice and the associated disclaimer. ////
////                                                              ////
//// This source file is free software; you can redistribute it   ////
//// and/or modify it under the terms of the GNU Lesser General   ////
//// Public License as published by the Free Software Foundation; ////
//// either version 2.1 of the License, or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful, but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE.  See the GNU Lesser General Public License for more ////
//// details.                                                     ////
////                                                              ////
//// You should have received a copy of the GNU Lesser General    ////
//// Public License along with this source; if not, download it   ////
//// from http://www.opencores.org/lgpl.shtml                     ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
`timescale 1ns / 10ps


//
// Number of bits used for devider register. If used in system with
// low frequency of system clock this can be reduced.
// Use SPI_DIVIDER_LEN for fine tuning theexact number.
//
//`define SPI_DIVIDER_LEN_8
`define SPI_DIVIDER_LEN_16
//`define SPI_DIVIDER_LEN_24
//`define SPI_DIVIDER_LEN_32

`ifdef SPI_DIVIDER_LEN_8
  `define SPI_DIVIDER_LEN       8    // Can be set from 1 to 8
`endif                                                          
`ifdef SPI_DIVIDER_LEN_16                                       
  `define SPI_DIVIDER_LEN       16   // Can be set from 9 to 16
`endif                                                          
`ifdef SPI_DIVIDER_LEN_24                                       
  `define SPI_DIVIDER_LEN       24   // Can be set from 17 to 24
`endif                                                          
`ifdef SPI_DIVIDER_LEN_32                                       
  `define SPI_DIVIDER_LEN       32   // Can be set from 25 to 32 
`endif

//
// Maximum nuber of bits that can be send/received at once. 
// Use SPI_MAX_CHAR for fine tuning the exact number, when using
// SPI_MAX_CHAR_32, SPI_MAX_CHAR_24, SPI_MAX_CHAR_16, SPI_MAX_CHAR_8.
//
//`define SPI_MAX_CHAR_128
//`define SPI_MAX_CHAR_64
//`define SPI_MAX_CHAR_32
//`define SPI_MAX_CHAR_24
`define SPI_MAX_CHAR_16
//`define SPI_MAX_CHAR_8

`ifdef SPI_MAX_CHAR_128
  `define SPI_MAX_CHAR          128  // Can only be set to 128 
  `define SPI_CHAR_LEN_BITS     7
`endif
`ifdef SPI_MAX_CHAR_64
  `define SPI_MAX_CHAR          64   // Can only be set to 64 
  `define SPI_CHAR_LEN_BITS     6
`endif
`ifdef SPI_MAX_CHAR_32
  `define SPI_MAX_CHAR          32   // Can be set from 25 to 32 
  `define SPI_CHAR_LEN_BITS     5
`endif
`ifdef SPI_MAX_CHAR_24
  `define SPI_MAX_CHAR          24   // Can be set from 17 to 24 
  `define SPI_CHAR_LEN_BITS     5
`endif
`ifdef SPI_MAX_CHAR_16
  `define SPI_MAX_CHAR          16   // Can be set from 9 to 16 -----MODIFICADO------- 
  `define SPI_CHAR_LEN_BITS     4   //  --------MODIFICADO--------
`endif
`ifdef SPI_MAX_CHAR_8
  `define SPI_MAX_CHAR          8    // Can be set from 1 to 8 
  `define SPI_CHAR_LEN_BITS     3
`endif

//
// Number of device select signals. Use SPI_SS_NB for fine tuning the 
// exact number.
//
`define SPI_SS_NB_8
//`define SPI_SS_NB_16
//`define SPI_SS_NB_24
//`define SPI_SS_NB_32

`ifdef SPI_SS_NB_8
  `define SPI_SS_NB             4    // Can be set from 1 to 8 ----------MODIFICADO---------
`endif
`ifdef SPI_SS_NB_16
  `define SPI_SS_NB             16   // Can be set from 9 to 16
`endif
`ifdef SPI_SS_NB_24
  `define SPI_SS_NB             24   // Can be set from 17 to 24
`endif
`ifdef SPI_SS_NB_32
  `define SPI_SS_NB             32   // Can be set from 25 to 32
`endif

//
// Bits of WISHBONE address used for partial decoding of SPI registers.
//
`define SPI_OFS_BITS	          4:2

//
// Register offset
//
`define SPI_RX_0                0
`define SPI_RX_1                1
`define SPI_RX_2                2
`define SPI_RX_3                3
`define SPI_TX_0                0
`define SPI_TX_1                1
`define SPI_TX_2                2
`define SPI_TX_3                3
`define SPI_CTRL                4
`define SPI_DEVIDE              5
`define SPI_SS                  6

//
// Number of bits in ctrl register
//
`define SPI_CTRL_BIT_NB         14

//
// Control register bit position
//
`define SPI_CTRL_ASS            13
`define SPI_CTRL_IE             12
`define SPI_CTRL_LSB            11
`define SPI_CTRL_TX_NEGEDGE     10
`define SPI_CTRL_RX_NEGEDGE     9
`define SPI_CTRL_GO             8
`define SPI_CTRL_RES_1          7
`define SPI_CTRL_CHAR_LEN       6:0
module spi_shift (clk, rst, latch, byte_sel, len, lsb, go,
                  pos_edge, neg_edge, rx_negedge, tx_negedge,
                  tip, last, 
                  p_in, p_out, s_clk, s_in, s_out);

  parameter Tp = 1;
  
  input                          clk;          // system clock
  input                          rst;          // reset
  input                    [3:0] latch;        // latch signal for storing the data in shift register
  input                    [3:0] byte_sel;     // byte select signals for storing the data in shift register
  input [`SPI_CHAR_LEN_BITS-1:0] len;          // data len in bits (minus one)
  input                          lsb;          // lbs first on the line
  input                          go;           // start stansfer
  input                          pos_edge;     // recognize posedge of sclk
  input                          neg_edge;     // recognize negedge of sclk
  input                          rx_negedge;   // s_in is sampled on negative edge 
  input                          tx_negedge;   // s_out is driven on negative edge
  output                         tip;          // transfer in progress
  output                         last;         // last bit
  input                   [31:0] p_in;         // parallel in
  output     [`SPI_MAX_CHAR-1:0] p_out;        // parallel out
  input                          s_clk;        // serial clock
  input                          s_in;         // serial in
  output                         s_out;        // serial out
                                               
  reg                            s_out;        
  reg                            tip;
                              
  reg     [`SPI_CHAR_LEN_BITS:0] cnt;          // data bit count
  reg        [`SPI_MAX_CHAR-1:0] data;         // shift register
  wire    [`SPI_CHAR_LEN_BITS:0] tx_bit_pos;   // next bit position
  wire    [`SPI_CHAR_LEN_BITS:0] rx_bit_pos;   // next bit position
  wire                           rx_clk;       // rx clock enable
  wire                           tx_clk;       // tx clock enable
  
  assign p_out = data;
  
  assign tx_bit_pos = lsb ? {!(|len), len} - cnt : cnt - {{`SPI_CHAR_LEN_BITS{1'b0}},1'b1};
  assign rx_bit_pos = lsb ? {!(|len), len} - (rx_negedge ? cnt + {{`SPI_CHAR_LEN_BITS{1'b0}},1'b1} : cnt) : 
                            (rx_negedge ? cnt : cnt - {{`SPI_CHAR_LEN_BITS{1'b0}},1'b1});
  
  assign last = !(|cnt);
  
  assign rx_clk = (rx_negedge ? neg_edge : pos_edge) && (!last || s_clk);
  assign tx_clk = (tx_negedge ? neg_edge : pos_edge) && !last;
  
  // Character bit counter
  always @(posedge clk or posedge rst)
  begin
    if(rst)
      cnt <= #Tp {`SPI_CHAR_LEN_BITS+1{1'b0}};
    else
      begin
        if(tip)
          cnt <= #Tp pos_edge ? (cnt - {{`SPI_CHAR_LEN_BITS{1'b0}}, 1'b1}) : cnt;
        else
          cnt <= #Tp !(|len) ? {1'b1, {`SPI_CHAR_LEN_BITS{1'b0}}} : {1'b0, len};
      end
  end
  
  // Transfer in progress
  always @(posedge clk or posedge rst)
  begin
    if(rst)
      tip <= #Tp 1'b0;
  else if(go && ~tip)
    tip <= #Tp 1'b1;
  else if(tip && last && pos_edge)
    tip <= #Tp 1'b0;
  end
  
  // Sending bits to the line
  always @(posedge clk or posedge rst)
  begin
    if (rst)
      s_out   <= #Tp 1'b0;
    else
      s_out <= #Tp (tx_clk || !tip) ? data[tx_bit_pos[`SPI_CHAR_LEN_BITS-1:0]] : s_out;
  end
  
  // Receiving bits from the line
  always @(posedge clk or posedge rst)
  begin
    if (rst)
      data   <= #Tp {`SPI_MAX_CHAR{1'b0}};
`ifdef SPI_MAX_CHAR_128
    else if (latch[0] && !tip)
      begin
        if (byte_sel[3])
          data[31:24] <= #Tp p_in[31:24];
        if (byte_sel[2])
          data[23:16] <= #Tp p_in[23:16];
        if (byte_sel[1])
          data[15:8] <= #Tp p_in[15:8];
        if (byte_sel[0])
          data[7:0] <= #Tp p_in[7:0];
      end
    else if (latch[1] && !tip)
      begin
        if (byte_sel[3])
          data[63:56] <= #Tp p_in[31:24];
        if (byte_sel[2])
          data[55:48] <= #Tp p_in[23:16];
        if (byte_sel[1])
          data[47:40] <= #Tp p_in[15:8];
        if (byte_sel[0])
          data[39:32] <= #Tp p_in[7:0];
      end
    else if (latch[2] && !tip)
      begin
        if (byte_sel[3])
          data[95:88] <= #Tp p_in[31:24];
        if (byte_sel[2])
          data[87:80] <= #Tp p_in[23:16];
        if (byte_sel[1])
          data[79:72] <= #Tp p_in[15:8];
        if (byte_sel[0])
          data[71:64] <= #Tp p_in[7:0];
      end
    else if (latch[3] && !tip)
      begin
        if (byte_sel[3])
          data[127:120] <= #Tp p_in[31:24];
        if (byte_sel[2])
          data[119:112] <= #Tp p_in[23:16];
        if (byte_sel[1])
          data[111:104] <= #Tp p_in[15:8];
        if (byte_sel[0])
          data[103:96] <= #Tp p_in[7:0];
      end
`else
`ifdef SPI_MAX_CHAR_64
    else if (latch[0] && !tip)
      begin
        if (byte_sel[3])
          data[31:24] <= #Tp p_in[31:24];
        if (byte_sel[2])
          data[23:16] <= #Tp p_in[23:16];
        if (byte_sel[1])
          data[15:8] <= #Tp p_in[15:8];
        if (byte_sel[0])
          data[7:0] <= #Tp p_in[7:0];
      end
    else if (latch[1] && !tip)
      begin
        if (byte_sel[3])
          data[63:56] <= #Tp p_in[31:24];
        if (byte_sel[2])
          data[55:48] <= #Tp p_in[23:16];
        if (byte_sel[1])
          data[47:40] <= #Tp p_in[15:8];
        if (byte_sel[0])
          data[39:32] <= #Tp p_in[7:0];
      end
`else
    else if (latch[0] && !tip)
      begin
      `ifdef SPI_MAX_CHAR_8
        if (byte_sel[0])
          data[`SPI_MAX_CHAR-1:0] <= #Tp p_in[`SPI_MAX_CHAR-1:0];
      `endif
      `ifdef SPI_MAX_CHAR_16
        if (byte_sel[0])
          data[7:0] <= #Tp p_in[7:0];
        if (byte_sel[1])
          data[`SPI_MAX_CHAR-1:8] <= #Tp p_in[`SPI_MAX_CHAR-1:8];
      `endif
      `ifdef SPI_MAX_CHAR_24
        if (byte_sel[0])
          data[7:0] <= #Tp p_in[7:0];
        if (byte_sel[1])
          data[15:8] <= #Tp p_in[15:8];
        if (byte_sel[2])
          data[`SPI_MAX_CHAR-1:16] <= #Tp p_in[`SPI_MAX_CHAR-1:16];
      `endif
      `ifdef SPI_MAX_CHAR_32
        if (byte_sel[0])
          data[7:0] <= #Tp p_in[7:0];
        if (byte_sel[1])
          data[15:8] <= #Tp p_in[15:8];
        if (byte_sel[2])
          data[23:16] <= #Tp p_in[23:16];
        if (byte_sel[3])
          data[`SPI_MAX_CHAR-1:24] <= #Tp p_in[`SPI_MAX_CHAR-1:24];
      `endif
      end
`endif
`endif
    else
      data[rx_bit_pos[`SPI_CHAR_LEN_BITS-1:0]] <= #Tp rx_clk ? s_in : data[rx_bit_pos[`SPI_CHAR_LEN_BITS-1:0]];
  end
  
endmodule

