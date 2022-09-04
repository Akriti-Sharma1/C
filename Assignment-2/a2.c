#include "a2.h"
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int bitwise_xor(int value){
  char c;
  int val = KEY;
  int real = abs(val-value);
  return real;
}

char *my_itoa(int num, char *str)
{
  if(str == NULL)
  {
          return NULL;
  }
  sprintf(str, "%d", num);
  return str;
}

void left_fill_zeros(char* dest, const char* str, int length)
{
  sprintf(dest, "%.*d%s", (int)(length-strlen(str)), 0, str);
  //printf("%s", dest);
}

char *xor_encrypt(char c){
  int res_char = 0, i = 1, rem;
  int bin_character = (int)c;
        
	while (bin_character > 0)
	{
		rem = bin_character % 2;
		res_char = res_char + (i * rem);
		bin_character = bin_character / 2;
		i = i * 10;
	}

  
  //printf("%d\n", res_char);

  int res_key = 0, i1 = 1, rem1;
  int bin_key = (int)KEY;
        
	while (bin_key > 0)
	{
		rem1 = bin_key % 2;
		res_key = res_key + (i1 * rem1);
		bin_key = bin_key / 2;
		i1 = i1 * 10;
	}
  
  //printf("%d", res_key);
  char* snum = (char *) malloc(8*sizeof(char));
  char* real = (char *) malloc(8*sizeof(char));
  snum = my_itoa(res_char,snum);
  left_fill_zeros(real, snum, 7);
  //printf("BINARY CHAR: %s\n", real);
  free(snum);

  char* snum1 = (char *) malloc(7*sizeof(char));
  char* real1 = (char *) malloc(7*sizeof(char));
  snum1 = my_itoa(res_key,snum1);
  left_fill_zeros(real1, snum1, 7);
  //printf("BINARY KEY: %s\n", real1);
  free(snum1);
  //real[7] = ' ';
  //real1[7] = ' ';
  
  char* string = (char *) malloc(256*sizeof(char));
  //printf("%ld\n", strlen(real));
  
  for(int i = 0; i < strlen(real); i++){
    if(real[i] == real1[i]){
      string[i] = '0';
    } else{
      string[i] = '1';
    }
  }
  //printf("%s", string);
  
  
  //printf("%s", real);
	free(real);
  free(real1);
  return string;
}

char xor_decrypt(char *s){
  int res = 0;
  int j = strlen(s)-1;
  for(int i = 0; i < strlen(s); i++){
    if(s[i] == '1'){
      res += pow(2,j);
    }
    j--;
  }
  //printf("%d\n", res);
  char test = (char)res;
  //printf("%c", test);
  char* decrypted = (char *) malloc(sizeof(char)*257);
  decrypted = xor_encrypt(test);
  int res1 = 0;
  int j1 = strlen(s)-1;
  for(int i = 0; i < strlen(s); i++){
    if(decrypted[i] == '1'){
      res1 += pow(2,j1);
    }
    j1--;
  }
  //printf("%d", res1);
  char real = (char) res1;
  //printf("%c", real);
  free(decrypted);
  return real;
}

char* set_up_sc(char* msg){
  char *sc_string;
  sc_string = (char*)malloc(260*sizeof(char));
  
  int k = 16;
  //sc_string[0] = '1';
  //sc_string[1] = '1';
  // SETTING UP SC STR
  for(int i = 0; i < 256; i++){
    sc_string[i] = '0';
  }

  
  for(int j = 0; j<4; j++){
    sc_string[j] = '1';
    sc_string[j+11] = '1';
    sc_string[j+64] = '1';
    sc_string[j+75] = '1';
    sc_string[k] = '1';
    sc_string[k+11] = '1';
    sc_string[k+4] = '1';
    sc_string[k+15] = '1';
    k += 16;
  }
  sc_string[4] = '1';
  sc_string[15] = '1';
  sc_string[34] = '1';
  sc_string[45] = '1';

  int b = 176;
  for(int i = 176; i < 180; i++){
    sc_string[i] = '1';
    sc_string[i+64] = '1';
    sc_string[b] = '1';
    //sc_string[b+11] = '1';
    sc_string[b+4] = '1';
    //sc_string[b+15] = '1';
    b += 16;
  }
  sc_string[244] = '1';
  sc_string[255] = '1';
  sc_string[210] = '1';
  return sc_string;
}

char *gen_code(char *msg){
  char* sc_string = set_up_sc(msg);

  int i = 0; 
  int count = 0;
  char** array_of_bin = (char **) malloc(30*sizeof(char*));
  while(i < strlen(msg)){
    array_of_bin[i] = xor_encrypt(msg[i]);
    count++;
    //printf("%s\n", array_of_bin[i]);
    i++;
  }
  //printf("\n");
  int b = 0;
  int c = 5;
  
  for(int k = 0; k < count; k++){
    //printf("%s\n", array_of_bin[k]);
    for(int j = 0; j < 7; j++){
      if(sc_string[c] != '1' && c < 74){
        sc_string[c] = array_of_bin[b][j];
        //printf("Putting in %c at %d\n", array_of_bin[b][j], c);
        //c++;
      }else if (c<74){
        sc_string[c+10] = array_of_bin[b][j];
        //printf("Putting in %c at %d\n", array_of_bin[b][j], c+10);
        c+= 10;
      }
      c++;
    }
    b++;
  }
  int e = 5;
  int d = 85;
  if(count > 4){
    sc_string[73] = array_of_bin[4][0];
    sc_string[74] = array_of_bin[4][1];
    sc_string[80] = array_of_bin[4][2];
    sc_string[81] = array_of_bin[4][3];
    sc_string[82] = array_of_bin[4][4];
    sc_string[83] = array_of_bin[4][5];
    sc_string[84] = array_of_bin[4][6];
    int done_words = 4;
    for(int i = done_words; i < count-1; i++){
      for(int j = 0; j < 7; j++){
        if(sc_string[d] != '1'){
          sc_string[d] = array_of_bin[e][j];
          //printf("Putting in %c at %d\n", array_of_bin[e][j], d);
          //c++;
        }else{
          d+=5;
        }
        d++;
      }
      e++;
    }
    }
  char* null = xor_encrypt(0);
  
  //printf("%s\n", null);
  sc_string[d] = null[0];
  sc_string[d+1] = null[1];
  sc_string[d+2] = null[2];
  sc_string[d+3] = null[3];
  sc_string[d+4] = null[4];
  sc_string[d+5] = null[5];
  sc_string[d+6] = null[6];

  sc_string[255] = '1';
    
    

  /*int a = 0;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      printf("%c ",sc_string[a]);
      a++;
    }
    printf("\n");
  }*/
  //printf("%s", sc_string);
  //while(i <strlen(msg) != )
  return sc_string;
  
}

char* iterate_string(char *code){
  int start = 5; 
  char* simple_sc = set_up_sc("hi");
  char* array_of_bin = (char *) malloc(30*sizeof(char));
  char temp[7];
  int a = 0;
  int i = 0;
  
  for(int j = 0; j < 74; j++){
    if(simple_sc[start] != '1' && start < 74){
      //printf("%c\n", xor_decrypt(temp));
      //printf("%d\n", start);
      if(a < 7){
        temp[a] = code[start];
        a++;
        start++;
        } else if(a >= 7){
        //printf("%s\n", temp);
        array_of_bin[i] = xor_decrypt(temp);
        //printf("%d\n", i);
        i++;
        a = 0;
        }
      
      //printf("%s\n", array_of_bin[i]);
      //start++;
    } else if (start<74){
      start += 10;
    }
    }
    temp[0] = code[73];
    temp[1] = code[74];
    temp[2] = code[80];
    temp[3] = code[81];
    temp[4] = code[82];
    temp[5] = code[83];
    temp[6] = code[84];
    
    array_of_bin[4] = xor_decrypt(temp);
    start = 85;
    a = 0;
    i = 5;
  for(int j = 85; j < 255; j++){
    //printf("%c\n", simple_sc[start]);
    if(simple_sc[start] != '1' && start < 256){
      //printf("%c\n", xor_decrypt(temp));
      //printf("%d\n", start);
      if(a < 7){
        temp[a] = code[start];
        a++;
        start++;
        } else if(a >= 7){
        //printf("%c\n", xor_decrypt(temp));
        //printf("%s\n", temp);
        array_of_bin[i] = xor_decrypt(temp);
        //printf("%d\n", i);
        i++;
        a = 0;
        }
      
      //printf("%s\n", array_of_bin[i]);
      //start++;
    } else if(start<256){
      start += 5;
    }
  }
  return array_of_bin;
}

char *read_code(char *code){
  char* array_of_bin = iterate_string(code);
  char* string = (char *) malloc(30*sizeof(char));
  for(int i = 0; i < 14; i++){
    //printf("%c\n", array_of_bin[i]);
    if(array_of_bin[i] != 0){
      string[i] = array_of_bin[i];
    }else{
      break;
    }
  }
  //printf("%s", string);
  return string; 
  }

int myAtoi(char* str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
 
    return res;
}

char *compress(char *code){
  int start = 0;
  int temp = 0;
  int a = 0;
  char* str = (char *) malloc(40*sizeof(char));
  char* string = (char *)malloc(64*sizeof(char));
  //printf("%s\n", code);
  for(int i = 0; i < 256; i+= 4){
    if(code[i+3] == '1'){
      temp += 1;
    }
    if(code[i+2] == '1'){
      temp += 2; 
    }
    if(code[i+1] == '1'){
      temp += 4;
    }
    if(code[i] == '1'){
      temp += 8;
    }
    str = my_itoa(temp, str);
    //printf(" %s\n", str);
    //printf("%d\n",temp);
    //printf("%s", str);
    if(temp == 10){
      *str = 'A';
    } else if(temp == 11){
      *str = 'B';
    } else if(temp == 12){
      *str = 'C';
    } else if(temp == 13){
      *str = 'D';
    } else if(temp == 14){
      *str = 'E';
    } else if(temp == 15){
      *str = 'F';
    } else if(temp == 16){
      *str = 'G';
    }
    string[a] = *str;
    temp = 0;
    a++;
  }
  //printf("%s", string);
  return string;
  }

char *decompress(char *code){
  char* string = (char *)malloc(257*sizeof(char));
  //string = set_up_sc(code);
  for(int i = 0; i < 256; i++){
    string[i] = '0';
  }
  int i = 0;
  int a = 0;
  while (code[i])
    {
        switch (code[i])
        {
        case '0':
          string[a] = '0';
          string[a+1] = '0';
          string[a+2] = '0';
          string[a+3] = '0';
          a+= 4;
          break;
        case '1':
          string[a] = '0';
          string[a+1] = '0';
          string[a+2] = '0';
          string[a+3] = '1';
          a+= 4;
          break;
        case '2':
          string[a] = '0';
          string[a+1] = '0';
          string[a+2] = '1';
          string[a+3] = '0';
          a+= 4;
          break;
        case '3':
          string[a] = '0';
          string[a+1] = '0';
          string[a+2] = '1';
          string[a+3] = '1';
          a+= 4;
          break;
        case '4':
          string[a] = '0';
          string[a+1] = '1';
          string[a+2] = '0';
          string[a+3] = '0';
          a+= 4;
          break;
        case '5':
          string[a] = '0';
          string[a+1] = '1';
          string[a+2] = '0';
          string[a+3] = '1';
          a+= 4;
          break;
        case '6':
          string[a] = '0';
          string[a+1] = '1';
          string[a+2] = '1';
          string[a+3] = '0';
          a+= 4;
          break;
        case '7':
          string[a] = '0';
          string[a+1] = '1';
          string[a+2] = '1';
          string[a+3] = '1';
          a+= 4;
          break;
        case '8':
          string[a] = '1';
          string[a+1] = '0';
          string[a+2] = '0';
          string[a+3] = '0';
          a+= 4;
          break;
        case '9':
          string[a] = '1';
          string[a+1] = '0';
          string[a+2] = '0';
          string[a+3] = '1';
          a+= 4;
          break;
        case 'A':
          string[a] = '1';
          string[a+1] = '0';
          string[a+2] = '1';
          string[a+3] = '0';
          a+= 4;
          break;
        case 'B':
          string[a] = '1';
          string[a+1] = '0';
          string[a+2] = '1';
          string[a+3] = '1';
          a+= 4;
          break;
        case 'C':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '0';
          string[a+3] = '0';
          a+= 4;
          break;
        case 'D':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '0';
          string[a+3] = '1';
          a+= 4;
          break;
        case 'E':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '1';
          string[a+3] = '0';
          a+= 4;
          break;
        case 'F':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '1';
          string[a+3] = '1';
          a+= 4;
          break;
        case 'a':
          string[a] = '1';
          string[a+1] = '0';
          string[a+2] = '1';
          string[a+3] = '0';
          a+= 4;
          break;
        case 'b':
          string[a] = '1';
          string[a+1] = '0';
          string[a+2] = '1';
          string[a+3] = '1';
          a+= 4;
          break;
        case 'c':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '0';
          string[a+3] = '0';
          a+= 4;
          break;
        case 'd':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '0';
          string[a+3] = '1';
          a+= 4;
          break;
        case 'e':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '1';
          string[a+3] = '0';
          a+= 4;
          break;
        case 'f':
          string[a] = '1';
          string[a+1] = '1';
          string[a+2] = '1';
          string[a+3] = '1';
          a+= 4;
          break;
        default:
            printf("\n Invalid hexa digit %c ", code[i]);
            return 0;
        }
        i++;
    }
  /*for(i = 0; i < 256; i++){
    for(int j = 0; j < 16; j++){
      printf("%c", string[j]);
    }
    printf("\n");
  }*/
  //printf("%s", string);
  return string;
  }

int calc_ld(char *sandy, char *cima){
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(sandy);
    s2len = strlen(cima);
    unsigned int column[s1len + 1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (sandy[y-1] == cima[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return column[s1len];
}


/*int main(){
  int val = bitwise_xor(66);
  printf("%d", val);
  //char* test = xor_encrypt('C');
  //printf("%c\n", xor_decrypt("0000000"));
  //char* code = gen_code("Program in C!");
  //printf("%s", code);
  //printf("%s",read_code(code));
  //char* hexacode = compress(code);
  //decompress(hexacode);
  //printf("%d", calc_ld("COMMENCE", "PROCRASTINATING"));
  
}*/