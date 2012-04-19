/*
 * @Proj:Tiger Compiler
 *
 * @FileDesc:{ /$ Utils Header File$\ }
 * 
 * @Author:{
 *  Name  : Adrian Hu
 *  Email : adrain.f.tepes@gmail.com
 * }
 * 
 *
 * @Progress:{
 * 
 * }
 * 
 * @Module:{
 *  LocalMoudle:utils
 * }
 * 
 * @Doc:{
 *
 * }
 ****** THIS LINE IS 80 CHARACTERS WIDE - DO *NOT* EXCEED 80 CHARACTERS! ******/

/* Calculate the number of array's items */
#define ARY_ITEM_NUMBER(array) (int)(sizeof(array)/ sizeof((array)[0]))
