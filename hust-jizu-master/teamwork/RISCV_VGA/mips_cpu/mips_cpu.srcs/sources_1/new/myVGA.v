`timescale 1ns / 1ps
//
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/12 20:29:36
// Design Name: 
// Module Name: vga_test
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//
// // Company:  // Engineer:  //  
   // Create Date: 2014/09/22 22:18:12 // Design Name:  // Module Name: a1 // Project Name:  // Target Devices:  // Tool Versions:  // Description:  //  
   // Dependencies:  //  
   // Revision: 
   // Revision 0.01 - File Created // Additional Comments: //  
   //  
   //640*480@60HZ,时钟像素：25MHZ module a1( 

module myvga(
 nclk,rst_n, hsync,vsync, vga_r,r0,r1,r2,vga_g,g0,g1,g2,vga_b,b0,b1,b2,display
    ); 
    input [32*32-1:0] display;
    input nclk;         //内部100M时钟输入 
    input rst_n;      //复位键 
    output reg  hsync,vsync;    //场同步，行同步信号 
    output vga_r,vga_g,vga_b,r0,r1,r2,g0,g1,g2,b0,b1,b2;    //颜色信号输出  
    reg[10:0] x_cnt;      //行坐标计数，为后面行的0或者1及具体像素点的位置做准备
    reg[9:0] y_cnt;        //列坐标计数，为后面列的0或者1及具体像素点的位置做准备
    reg clk;              //实现4分频后的像素点频率 //100M到25M分频器设计 
    reg[2:0]clk_cnt;
    reg[8:0]flag1;
    reg[8:0]flag2;
    reg[26:0]count;
    wire valid = (x_cnt>=11'd144)&&(x_cnt<=11'd784)&&(y_cnt>=10'd35)&&(y_cnt<=10'd515); 
    wire [9:0] xpos = x_cnt; wire [9:0] ypos = y_cnt;
    reg dis[1023:0];  
    reg [32*32:0]green;
    initial begin
        x_cnt = 0;
        y_cnt = 0;
        flag1 = 0;
        flag2 = 0;
        count = 0;
        green[0] = 0;
    end
    initial        //寄存器变量赋初值 
      begin 
        clk=1'b0; 
        clk_cnt=3'd0;
      end 
    //红绿蓝的其他三个端口 
    //assign r0=1'b0; assign r1=1'b0; assign r2=1'b0; 
   // assign g0=1'b0; assign g1=1'b0; assign g2=1'b0;
     assign b0=1'b0; assign b1=1'b0; assign b2=1'b0;  
    always @(negedge nclk) 
     begin 
      clk_cnt = clk_cnt + 1; 
      if(clk_cnt==3'd2) 
      clk =1'b1; 
      else if(clk_cnt==3'd4)  
         begin 
          clk=1'b0;
          clk_cnt=3'd0; 
         end 
      end  //实现四分频

     //VGA显示的设计     //像素点的计数 
    always@(posedge clk or negedge rst_n)
     begin 
       if(rst_n)
         x_cnt=11'd0;   //复位行坐标置零
      else if(x_cnt==11'd800)//行有800个象素点就重扫
         x_cnt=11'd0; 
      else
         x_cnt = x_cnt + 1'b1;     //依次扫描行 
      end 
       //行的计数 
    always@(posedge clk or negedge rst_n) 
        if(rst_n)
          y_cnt = 10'd0; //复位，列置零
        else if(y_cnt==10'd525)//列有525个象素点就重扫
         y_cnt=11'd0; 
        else if(x_cnt==11'd800)//一行到头换下一列
         y_cnt = y_cnt + 1'b1;
     //定义屏幕显示区域 


    //行时序的确定 
    always@(posedge clk or negedge rst_n) 
        if(rst_n)
            hsync =1'b0;//复位从0开始 
        else if(x_cnt==11'd0)
            hsync=1'b0; 
        else if(x_cnt==11'd96) 
            hsync=1'b1; 
   //帧时序的确定 
    always@(posedge clk or negedge rst_n) 
        if(rst_n) 
           vsync =1'b0;  //复位从0开始 
        else if(y_cnt==10'd0) 
           vsync=1'b0; 
        else if(y_cnt==10'd2) 
           vsync=1'b1; 
    
   
   
//My display   
 
   integer i,j;
    always@(posedge clk) begin
            for(i = 0; i < 32; i = i+1) begin
                for(j = 0; j < 32; j = j+1) begin
                    dis[i*32+j] = ((xpos>=704-15-j*15)&&(xpos<=704-j*15))&&((ypos>=515-i*15-15)&&(ypos<=515-i*15)); 
                end 
            end 
    end
    
    
    
    assign vga_r= 0;             
    assign vga_b= 0; 
       
        integer ii;



//        reg [32*32-1:0] show;
//        always@(posedge clk) begin
//                   for(ii = 0; ii < 32*32; ii = ii+1) begin
//                        show[ii] =1;    //instructionmen[ii]为1说明此处有像素点需要显示
//                   end
//                   show[500] = 0;
//                   show[510] = 0;
//        end
        
        always@(posedge clk) begin
            for(ii = 0; ii < 32*32; ii = ii+1) begin
                 green[ii+1] = green[ii] | (dis[ii] );    //display[ii]为1说明此处有像素点需要显示
                 green[ii] = 0;
            end
        end
        
     //assign green = 1;
     //assign vga_g = valid? 1'b1:1'b0 ; 
    assign vga_g = green[32*32];
    assign g0 = green[32*32];
    assign g1 = green[32*32];
    assign g2 = green[32*32];
    //划分不同显示界面 
//    wire a_dis=((xpos>=144)&&(xpos<=784))&&((ypos>=35)&&(ypos<=135));//b
//    wire b_dis=((xpos>=200)&&(xpos<=700))&&((ypos>=136)&&(ypos<=185)); //r
//    wire c_dis=((xpos>=144)&&(xpos<=784))&&((ypos>=415)&&(ypos<=515)); //b
//    wire d_dis=((xpos>=200)&&(xpos<=700))&&((ypos>=365)&&(ypos<=415)); //r
//    wire e_dis=((xpos>=200)&&(xpos<=250))&&((ypos>=186)&&(ypos<=366)); //r
//    wire f_dis=((xpos>=650)&&(xpos<=699))&&((ypos>=186)&&(ypos<=366)); //r
//     wire h_dis=((xpos>=144)&&(xpos<=199))&&((ypos>=136)&&(ypos<=414));//b
//      wire i_dis=((xpos>=700)&&(xpos<=784))&&((ypos>=136)&&(ypos<=414));//b
//       always@(posedge clk or negedge rst_n)   
//                begin
//                 if(rst_n)
//                       begin
//                       count<=0;
//                       flag1<=0;
//                       flag2<=0;
//                       end
//                   else
//                   begin
//                      count=count+1;
//                      if(count==27'b11110100001001000000)
//                      begin
//                             count<=0;
//                             if(flag1==9'd0)
//                               begin
//                                   if(flag2==9'd0)
//                                     begin
//                                         flag1=flag1+1;
//                                      end
//                                      else
//                                        begin
//                                        flag2=flag2-1;
//                                        end
//                                 end
//                                 if(flag2==9'd0)
//                                  begin
//                                      if(flag1==9'd348)
//                                        begin
//                                            flag2=flag2+1;
//                                         end
//                                       else
//                                       begin
//                                           flag1=flag1+1;
//                                        end
//                                   end
//                                    if(flag1==9'd348)
//                                       begin
//                                          if(flag2==9'd237)
//                                            begin
//                                               flag1=flag1-1;
//                                              end
//                                             else
//                                             begin
//                                               flag2=flag2+1;
//                                              end
//                                      end
//                                if(flag2==9'd237)
//                                        begin
//                                              if(flag1==9'd0)
//                                                begin
//                                                   flag2=flag2-1;
//                                                 end
//                                                else
//                                                begin
//                                                   flag1=flag1-1;
//                                                    end
//                                   end

//                             end
//                          end
//                          end
//                 wire g_dis=((xpos>=251+flag1)&&(xpos<=300+flag1))&&((ypos>=136+flag2)&&(ypos<=176+flag2)); //g

    //RGB像素点的赋值 
//    assign vga_r= valid?(d_dis |b_dis|e_dis |f_dis):1'b0; 
//          assign vga_b= valid?(a_dis |c_dis|h_dis |i_dis):1'b0; 
//        assign vga_g= valid?g_dis:1'b0; 

//    assign vga_r= valid?(dis):1'b0; 
//    assign r0= valid?(1'b1):1'b0; 
//    assign r1= valid?(1'b1):1'b0; 
//    assign r2= valid?(1'b1):1'b0; 
//    assign vga_b= valid?(1'b0):1'b0; 
//    assign vga_g= valid?g_dis:1'b0; 

endmodule