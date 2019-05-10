#include <stdio.h>
#include <stdlib.h>	
#include "intarr.h"

/* LAB 6 TASK 2 */

/*
  Save the entire array ia into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  intarr_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.
  
  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON array:
  [ 100, 200, 300 ]
  
  The following lines are a valid JSON array:
  [ 
   100, 
   200, 
   300 
  ]
*/
int intarr_save_json( intarr_t* ia, const char* filename ){
	if (ia==NULL || ia->data==NULL || filename==NULL)
        return 1;
    
    
    FILE *f=fopen(filename,"w+");

    fprintf(f,"[");

    for (int i=0;i<ia->len;i++){
        fprintf(f," %d",ia->data[i]);
        if (i!=ia->len-1)
            fprintf(f,",");      
    }
    fprintf(f," ]");
    fclose(f);
    return 0;
}

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.
*/
intarr_t* intarr_load_json( const char* filename ){
	if (filename == NULL) 
        return NULL;
    
    FILE * file;
    file=fopen(filename, "r+");
    if (file==NULL) 
        return NULL;
    int i=0;
    int num=0;
    char a;
    int y;
    intarr_t *new=malloc(sizeof(intarr_t));
    
    while (feof(file)==0){
        a=getc(file);
        if (a==','){
            num++;
        }
    }
    fseek(file,0,SEEK_SET);

    if (num==0){
        new->len=0;
        new->data=NULL;
        return new;
    }
    new->len=num+1;
    new->data=malloc(sizeof(int)*new->len);
    
    while(i<new->len){
        while (fscanf(file, "%d",&y)!=1)
            fseek(file, 1, SEEK_CUR);
        
        new->data[i]=y;
        i++;
    }
    fseek(file,0,SEEK_END);

    fclose(file);
    return new;
}
