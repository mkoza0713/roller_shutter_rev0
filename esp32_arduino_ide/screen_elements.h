//nav
uint32_t button_name_1 = 'button_1';
String button_label_1 = "WSTECZ";
int button_1[]{
  1,    //x  0
  1,    //y  1
  104,  //wide  2
  40,   //height  3
  15,   // round  4
};

uint32_t button_name_2 = 'button_2';
String button_label_2 = "NASTEPNY";
int button_2[]{
  215,  //x
  1,    //y
  104,  //wide
  40,   //height
  15,   // round
};


//Panele:
int buttons_positions[6][5]{  //max 6 elements
  /*{x0, y0, wide, heigh, round}*/
  { 1, 71, 150, 50, 15 },
  { 169, 71, 150, 50, 15 },
  { 1, 131, 150, 50, 15 },
  { 169, 131, 150, 50, 15 },
  { 1, 191, 150, 50, 15 },
  { 169, 191, 150, 50, 15 }
} ;
// int buttons_positions[6][5]{  //max 6 elements
//   /*{x0, y0, wide, heigh, round}*/
//   { 1, 71, 150, 60, 15 },
//   { 169, 71, 150, 60, 15 },
//   { 1, 146, 150, 60, 15 },
//   { 169, 146, 150, 60, 15 },
//   { 1, 221, 150, 60, 15 },
//   { 169, 221, 150, 60, 15 }
// } ;

String button_label_3_1 = "PARTER POM. ";
String button_label_3_2 = "MIESZKALNE";
int button_3[]{
  1,    //x
  71,   //y
  150,  //wide
  60,   //height
  15,   // round
};
String button_label_4_1 = "PARTER POM. ";
String button_label_4_2 = "TECHNICZNE";
int button_4[]{
  1,    //x
  146,  //y
  150,  //wide
  60,   //height
  15,   // round
};
String button_label_5_1 = "PIETRO POM. ";
String button_label_5_2 = "TECHNICZNE";
int button_5[]{
  169,  //x
  71,   //y
  150,  //wide
  60,   //height
  15,   // round
};
String button_label_6_1 = "PIETRO POM. ";
String button_label_6_2 = "MIESZKALNE";
int button_6[]{
  169,  //x
  146,  //y
  150,  //wide
  60,   //height
  15,   // round
};

//check-box
byte cb_y1 = 70;                 //pozycja checkboxa na lcd w osi y
byte frame1 = 20;                //rozmiar check boxa
byte cb_row_space = frame1 + 5;  //odleglosc pomiedzy wierszami
