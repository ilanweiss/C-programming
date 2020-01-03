//And let the games begin

int numStrsInList(const char* strList) {
//Youv'e sent a wrong pointer to here that is not to a string, Not nice!
   if(strList == NULL){
        return -1;
        }
    int i , size = 0, count=0;
//As long as we havn't hit the termenting '\0''\0' get the size.
    while (!((strList[size] == '\0' ) && (strList[size+1]=='\0'))){
        size++;
        }
//If it is empty there are no words so we can return 0.
    if (size<1) return count;
//Lets go over the list again not so efficiant, shold have done the count
// already but not going to change it now since it works.
    for (i=0;i<size;i++){
        if (strList[i]=='\0'){
            count++;
        }
    }
//Must not forget that we didn't count.
return count+1;
}

int strListLen(const char* strList) {
//Youv'e sent a wrong pointer to here that is not to a string, Not nice!
   if(strList == NULL){
        return -1;
        }
    int i=0;
//As long as we havn't hit the termenting '\0''\0' count the char.
    while (!((strList[i] == '\0' ) && (strList[i+1]=='\0'))){
        i++;
        }
    return i;
}
int emptyStrList(char* target) {
//Youv'e sent a wrong pointer to here that is not to a string, Not nice!
    if(target == NULL){
        return -1;
        }
    int size = 0;
    while (!((target[size] == '\0' ) && (target[size+1]=='\0'))){
        size++;
        }
//if you don't leave me space i can't put in the 2 '\0' .
   if(size < 2){
        return -1;
        }
   target[0]='\0';
   target[1]='\0';
   return 0;
}

int strListFromWords(const char* source, char* target, int buffSize) {
//If youv'e sent me wrong things to here, i won't play , Not nice!
    if ((buffSize < 2)||(source == NULL)||(target == NULL)){
        return -1;
        }
    int size = 0, words=0, chars=0 ;
//Don't start with spaces they are just a waste of space,
// i don't need to clean up after you!
    while (isspace(source[size++]));
//while we are still in the string go on and on and on....
   while (source[size]){
//If it is a charecter we will need it so add it to are chars count.
        if (!(isspace(source[size]) )){
                chars++;
                }
//If we have a space and yet before we didn't, we have finished a word,yay!
        if ((!(isspace(source[size-1])))  && ((isspace(source[size]))) ){
                words++;
                }
        size++;
        }
//Wow that toke loads of time, did we finish on a space?
//if we did we have an extra word, shit that isn't good, get rid of it!
    if (isspace(source[size-1])){
        words--;
        }
//Checking you we are left with room for what we need......
    if ( chars + words   >  buffSize - 3 ) {
        emptyStrList(target);
        return 0;
        }
    int  i = 0, j = 0;
//Let's start copying from one another, start by jumping over the spaces
    while (isspace(source[i])){
        i++;
        }
//Now to the real work
    while (source[i]){
         if (isspace(source[i])) {
//Finished a word, Yay, end the string and move to the next one in the list
            target[j++]='\0';
            while (isspace(source[i])) {
                i++;
                }
            }
        else {
//In the words of CS students:"just copy man!"
                target[j++] = source[i++];
                }
        }
//If we finished the while with a space we only need to add the termenting '\0'
    if (j > buffSize - 2){
        target[j]='\0';
        }
//Otherwise end with '\0''\0'
        else{
             target[j]='\0';
             target[j+1]='\0';
        }
//Call our privious function and give back the number of words in target!
    return numStrsInList(target);
 }
//Time for Bran the builder to get to work
char* createStrList(const char* str) {
//Or was it Bob? anyways NULL no point send it back
    if (str == NULL)
        return NULL;
    int size = 0, words=0, chars=0 ;
    while (isspace(str[size])){
//In the words of Van:" Might as well jump. Jump!Go ahead, jump".
        size++;
        }
//Same Same no diffrent count chars count words check if ends with space.
    while (str[size]){
        if (!(isspace(str[size]) )){
                chars++;
                }
        else {
                if ((!(isspace(str[size+1])))  && ((isspace(str[size]))) ){
                    words++;
                    }
                }
        size++;
        }
    if ((isspace(str[size-1])) && (words > 0)) {
        words--;
        }
//Get size of wanted target.
    int buffSize = words + chars + 2;
    char* target;
//Allocet Memory suficiant for target.
    target = malloc_wrapper(buffSize*sizeof(char));
//If we didn't manage admit faiiure & return NULL.
    if (!target) return NULL;
//Make the given string in to a string listin target and pray to Allah that it works.
    strListFromWords(str, target, buffSize);
//Praise Jesus it worked, Return the pointer target.
    return target;
}

char* nextStrInList(char* stringList) {
//Make some static veriables that will remeber what others have forgoten.
    static int word = 0,ch=0;
    static char *str = NULL;
//If string list is NULL forget everything and return nothing(i meen NULL)..
    if (stringList == NULL){
        word=0;
        ch=0;
        return NULL;
        }
//Checke if we are in the same list, if not just forget it.
    if (str != stringList) {
        str = stringList;
        word = 0;
        ch = 0;
        }
//if we are at the begining we can say let there be the first place in this string
// & it shall be so.
    if (word == 0){
        word++;
        return &stringList[ch];
    }
//If we have gone by all the words we can leave.
    if ( word  >= numStrsInList(stringList) )
        return NULL;
//Advance till thenext word starts.
    while(stringList[ch++]!= '\0');
    word++;
//Return the start of the next word.
    return &stringList[ch];
}

/*********************************************************************************/
/**********    YOUR  SOLUTUON TO PROBLEM 2.1 - 2.5 UNDER HERE         ************/
/*********************************************************************************/
int strcmpInList(char* strList1, char* strList2, int k) {
// check for if the string list is null
     if ((strList1 == NULL) || (strList2 == NULL)) return -10;
// check if both string lists have length of at least k
     if ((numStrsInList(strList1) < k) && (numStrsInList(strList2) < k)) return 0;
     if ((numStrsInList(strList1) < k) && (numStrsInList(strList2) >= k)) return -1;
     if ((numStrsInList(strList1) >= k) && (numStrsInList(strList2) < k)) return 1;
     int i;
     char *word1, *word2;
     nextStrInList(NULL);
// get the kth string for each string list
     for (i = 0; i < k; i++) {
         word1 = nextStrInList(strList1);
     }
     nextStrInList(NULL);
     for (i = 0; i < k; i++) {
        word2 = nextStrInList(strList2);
     }
//compare the kth strings of each list lexicographlly
     if (strcmp(word1, word2) < 0) return -1;
     if (strcmp(word1, word2) > 0) return 1;
     return 0;
}

int strListCmp(char* strList1, char* strList2, const int keys[], int numKeys) {
     int i;
     int cmp;
     for (i = 0; i < numKeys; i++) {
        cmp = strcmpInList(strList1, strList2, keys[i]);
        if (cmp != 0)  return cmp;
     }
     return 0;
   }
int strListSort(char** strListArr, int numLists, const int keys[], int numKeys) {
     if (strListArr == NULL) return -1;
     int i, j;
     for (i = 0; i < numLists; i++) {
          if (strListArr[i] == NULL) return -1;
          }
     char* temp;
     for (i = 0; i < numLists; i++) {
        j = i;
        while (j > 0 && strListCmp(strListArr[j - 1], strListArr[j], keys, numKeys) > 0) {
              temp = strListArr[j - 1];
              strListArr[j-1] = strListArr[j];
              strListArr[j] = temp;
              j--;
             }
        }
    return 0;
  }

int printStrLists(char** strListArr, int numLists) {
    if (strListArr == NULL) return -1;
    int  i, j;if 
    for (i = 0; i < numLists; i++) {
        for (j = 0; j < numStrsInList(strListArr[i]); j++){
             printf("%s", nextStrInList(strListArr[i]));
                if (j < numStrsInList(strListArr[i]) - 1)
                        printf("\t");
             }
                printf("\n");
        }
    return 0;
    }
int string2posInt(const char* str) {
    int  i, num = 0;
    if (str == NULL) return 0;
    for (i = 0 ; i < strlen(str); i++) {
        if ((str[i] < '0') || (str[i] > '9')) return 0;
        num = 10 * num + ( (int) str[i] - '0');
        }
    return num;
 }

