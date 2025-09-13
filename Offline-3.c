#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DOCS 50
#define MAX_LEN 5000
#define MAX_TOKENS 500
#define MAX_TOKEN_LEN 50
#define NUM_STOP_WORDS 8
int token_count = 0;
int token_exc_stp_count = 0;
int sorted_stm_count;

void sort_stem_tokens(char tokens[][MAX_TOKEN_LEN], int count) {
    char temp[MAX_TOKEN_LEN];
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(tokens[i], tokens[j]) > 0) {
                strcpy(temp, tokens[i]);
                strcpy(tokens[i], tokens[j]);
                strcpy(tokens[j], temp);
            }
        }
    }
    for(int i = 0; i < count-1; i++){
        for(int j = i+1; j < count; j++){
            if(strcmp(tokens[i],tokens[j]) == 0){
                for(int d = j; d < count-1;d++){
                    strcpy(tokens[d],tokens[d+1]);
                }
                j--;
                count--;
            }
        }
    }
    sorted_stm_count = count;
}
void normalize_case_all(char docs[][MAX_LEN], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; docs[i][j] != '\0'; j++){
            docs[i][j] = tolower(docs[i][j]);
        }
    }
}
void tokenize_all(char docs[][MAX_LEN], int n, char tokn[MAX_TOKENS][MAX_TOKEN_LEN]){
    for(int i = 0; i < n; i++){
        int j = 0;
        while(docs[i][j] != '\0'){
            while(docs[i][j] != '\0' && !isalnum(docs[i][j])){
                j++;
            }
            char word[MAX_TOKEN_LEN];
            int k = 0;
            while(docs[i][j] != '\0' && isalnum(docs[i][j]) && k < MAX_TOKEN_LEN){
                word[k++] = docs[i][j++];
            }
            word[k] = '\0';
            if(k > 0 && token_count < MAX_TOKENS){
                strcpy(tokn[token_count],word);
                token_count++;
            }
        }
    }
}
void remove_stop_words_all(char tokn[][MAX_TOKEN_LEN],char stp_wrd[NUM_STOP_WORDS][MAX_TOKEN_LEN],char tokn_stp_w[][MAX_TOKEN_LEN]){
    int d;
    int r = 0;
    for(int i = 0; i < token_count; i++){
        d = 0;
        for(int j = 0; j < NUM_STOP_WORDS;j++){
            if(strcmp(tokn[i],stp_wrd[j]) == 0){
                d = 1;
                break;
            }
        }
        if(d == 0){
            strcpy(tokn_stp_w[r++],tokn[i]);
            token_exc_stp_count++;
        }
    }
}
void stem_all_tokens(char tokn_stp_w[][MAX_TOKEN_LEN],char stm_wrd[][MAX_TOKEN_LEN]){
    int d = 0;
    int j;
    for(int i = 0; i < token_exc_stp_count; i++){
        j = strlen(tokn_stp_w[i]);
        if(j > 3 && strcmp(&tokn_stp_w[i][j - 3], "ing") == 0){
            strncpy(stm_wrd[d++],tokn_stp_w[i],strlen(tokn_stp_w[i])-3);
            stm_wrd[d][j-3] = '\0';
        }
        else if(j > 2 && strcmp(&tokn_stp_w[i][j - 2], "ed") == 0){
            strncpy(stm_wrd[d++],tokn_stp_w[i],strlen(tokn_stp_w[i])-2);
            stm_wrd[d][j-2] = '\0';
        }
        else if(j > 1 && tokn_stp_w[i][j - 1] =='s'){
            strncpy(stm_wrd[d++],tokn_stp_w[i],strlen(tokn_stp_w[i])-1);
            stm_wrd[d][j-1] = '\0';
        }
        else{
            strcpy(stm_wrd[d++],tokn_stp_w[i]);
        }
    }
}
double compute_tf(char word[], int doc_id, char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]){
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    char tokens_no_stop[MAX_TOKENS][MAX_TOKEN_LEN];
    char stemmed_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int count = 0, total = 0;
    int temp_token_count = 0;
    int temp_token_exc_stp_count = 0;

    for(int j = 0; docs[doc_id][j] != '\0'; j++){
        docs[doc_id][j] = tolower(docs[doc_id][j]);
    }

    int j = 0;
    while(docs[doc_id][j] != '\0'){
        while(docs[doc_id][j] != '\0' && !isalnum(docs[doc_id][j])){
            j++;
        }
        char word[MAX_TOKEN_LEN];
        int k = 0;
        while(docs[doc_id][j] != '\0' && isalnum(docs[doc_id][j]) && k < MAX_TOKEN_LEN){
            word[k++] = docs[doc_id][j++];
        }
        word[k] = '\0';
        if(k > 0 && temp_token_count < MAX_TOKENS){
            strcpy(tokens[temp_token_count],word);
            temp_token_count++;
        }
    }

    int d;
    int r = 0;
    for(int i = 0; i < temp_token_count; i++){
        d = 0;
        for(int j = 0; j < NUM_STOP_WORDS;j++){
            if(strcmp(tokens[i],stp_wrd[j]) == 0){
                d = 1;
                break;
            }
        }
        if(d == 0){
            strcpy(tokens_no_stop[r++],tokens[i]);
            temp_token_exc_stp_count++;
        }
    }

    d = 0;
    for(int i = 0; i < temp_token_exc_stp_count; i++){
        int len = strlen(tokens_no_stop[i]);
        if(len > 3 && strcmp(&tokens_no_stop[i][len - 3], "ing") == 0){
            strncpy(stemmed_tokens[d], tokens_no_stop[i], len - 3);
            stemmed_tokens[d++][len - 3] = '\0';
        }
        else if(len > 2 && strcmp(&tokens_no_stop[i][len - 2], "ed") == 0){
            strncpy(stemmed_tokens[d], tokens_no_stop[i], len - 2);
            stemmed_tokens[d++][len - 2] = '\0';
        }
        else if(len > 1 && tokens_no_stop[i][len - 1] == 's'){
            strncpy(stemmed_tokens[d], tokens_no_stop[i], len - 1);
            stemmed_tokens[d++][len - 1] = '\0';
        }
        else{
            strcpy(stemmed_tokens[d++], tokens_no_stop[i]);
        }
    }

    for(int i = 0; i < temp_token_exc_stp_count; i++){
        if(strcmp(word,stemmed_tokens[i])==0)
            count++;
    }
    if(temp_token_exc_stp_count == 0)
        return 0.0;
    return (double) count/temp_token_exc_stp_count;
}
double compute_idf(char word[], int doc_num, char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]){
    int doc_frq = 0;
    for(int doc_id = 0; doc_id < doc_num;doc_id++){  
        char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
        char tokens_no_stop[MAX_TOKENS][MAX_TOKEN_LEN];
        char stemmed_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
        int count = 0, total = 0;
        int temp_token_count = 0;
        int temp_token_exc_stp_count = 0;

        for(int j = 0; docs[doc_id][j] != '\0'; j++){
            docs[doc_id][j] = tolower(docs[doc_id][j]);
        }

        int j = 0;
        while(docs[doc_id][j] != '\0'){
            while(docs[doc_id][j] != '\0' && !isalnum(docs[doc_id][j])){
                j++;
            }
            char word[MAX_TOKEN_LEN];
            int k = 0;
            while(docs[doc_id][j] != '\0' && isalnum(docs[doc_id][j]) && k < MAX_TOKEN_LEN){
                word[k++] = docs[doc_id][j++];
            }
            word[k] = '\0';
            if(k > 0 && temp_token_count < MAX_TOKENS){
                strcpy(tokens[temp_token_count],word);
                temp_token_count++;
            }
        }

        int d;
        int r = 0;
        for(int i = 0; i < temp_token_count; i++){
            d = 0;
            for(int j = 0; j < NUM_STOP_WORDS;j++){
                if(strcmp(tokens[i],stp_wrd[j]) == 0){
                    d = 1;
                    break;
                }
            }
            if(d == 0){
                strcpy(tokens_no_stop[r++],tokens[i]);
                temp_token_exc_stp_count++;
            }
        }

        d = 0;
        for(int i = 0; i < temp_token_exc_stp_count; i++){
            int len = strlen(tokens_no_stop[i]);
            if(len > 3 && strcmp(&tokens_no_stop[i][len - 3], "ing") == 0){
                strncpy(stemmed_tokens[d], tokens_no_stop[i], len - 3);
                stemmed_tokens[d++][len - 3] = '\0';
            }
            else if(len > 2 && strcmp(&tokens_no_stop[i][len - 2], "ed") == 0){
                strncpy(stemmed_tokens[d], tokens_no_stop[i], len - 2);
                stemmed_tokens[d++][len - 2] = '\0';
            }
            else if(len > 1 && tokens_no_stop[i][len - 1] == 's'){
                strncpy(stemmed_tokens[d], tokens_no_stop[i], len - 1);
                stemmed_tokens[d++][len - 1] = '\0';
            }
            else{
                strcpy(stemmed_tokens[d++], tokens_no_stop[i]);
            }
        }

        for(int i = 0; i < temp_token_exc_stp_count; i++){
            if(strcmp(word,stemmed_tokens[i])==0){
                doc_frq++;
                break;
            }
        }
    }
    if(doc_frq == 0)
        return 0.0;
    return log10((double)MAX_DOCS /(1 + doc_frq));
}
void compute_tfidf_all(char word[MAX_TOKEN_LEN],int doc_num,char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]){
    double idf = compute_idf(word,doc_num,docs,stp_wrd);
    int doc_id = 0;
    for(int i = 0; i < doc_num; i++){
        printf("Document %d: %.4lf\n", i + 1, compute_tf(word, i, docs, stp_wrd)*idf);
    }
}
void display_stat(char s_tokn[][MAX_TOKEN_LEN],int doc_num,char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]){
    sort_stem_tokens(s_tokn,token_exc_stp_count);
    printf("\n========== TF ==========\n");
    printf("%-12s", "");  // empty for row labels
    for(int i = 0; i < doc_num; i++){
        printf("doc%-5d", i + 1);
    }
    printf("\n");
    for(int i = 0; i < sorted_stm_count; i++){
        printf("%-12s", s_tokn[i]);  // left-aligned token
        for(int j = 0; j < doc_num; j++){
            printf("%-8.4lf", compute_tf(s_tokn[i], j, docs, stp_wrd));
        }
        printf("\n");
    }
    printf("\n========== IDF ==========\n");
    printf("%-12s", "");  // empty for row labels
    printf("IDF\n");
    for(int i = 0; i < sorted_stm_count; i++){
        printf("%-12s", s_tokn[i]);  // left-aligned token
        printf("%-8.4lf", compute_idf(s_tokn[i], doc_num, docs, stp_wrd));
        printf("\n");
    }
    printf("\n========== TF-IDF ==========\n");
    printf("%-12s", "");  // empty for row labels
    for(int i = 0; i < doc_num; i++){
        printf("doc%-5d", i + 1);
    }
    printf("\n");
    for(int i = 0; i < sorted_stm_count; i++){
        printf("%-12s", s_tokn[i]);
        double idf = compute_idf(s_tokn[i],doc_num,docs,stp_wrd);
        int doc_id = 0;
        for(int j = 0; j < doc_num; j++){
            printf("%-8.4lf", compute_tf(s_tokn[i], j, docs, stp_wrd)*idf);
        }
        printf("\n");
    }
}

int main(){
    char documents[MAX_DOCS][MAX_LEN];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    char tokens_except_stop_words[MAX_TOKENS][MAX_TOKEN_LEN];
    char stemmed_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    char stop_words[NUM_STOP_WORDS][MAX_TOKEN_LEN] = {"the","is","a","an","and","in","of","to"};

    for(int i = 0; i < MAX_DOCS; i++){
        documents [i][0] = '\0';
    }
    
    printf("Welcome to the Document Processing System!\n\n  ");
    printf("set          - Prompt for the number of documents and their text.\n  ");
    printf("normalize    - Convert all documents to lowercase and display them.\n  ");
    printf("tokenize     - Tokenize all documents into words and display the tokens.\n  ");
    printf("remove_stop  - Remove stop words from tokens and display the filtered tokens.\n  ");
    printf("stem         - Apply simple stemming (remove suffixes like \"ing\",\"ed\",\"s\") and display results.\n  ");
    printf("tf           - Compute and display Term Frquency for a specified word across documents.\n  ");
    printf("idf          - Compute and display Inverse Document Frequency for a specified word.\n  ");
    printf("tfidf        - Compute and display TF-IDF scores for a specified word across documents.\n  ");
    printf("help         - Print the list of all available commands.\n  ");
    printf("stat         - Display TF,IDF, and TF-IDF for all tokens across all documents in a matrix format.\n  ");
    printf("exit         - Exit the program\n");

    int doc_num;
    int check_set = 0;
    int check_token = 0;
    
    while(1){
        printf("\nEnter command: ");
        char command[20];
        scanf("%s",command);

        if(strcmp(command,"set") == 0){
            printf("Enter number of documents (1-50) : ");
            scanf("%d",&doc_num);
            getchar();
            if(doc_num <= MAX_DOCS){
                for(int i = 0; i < doc_num; i++){
                    printf("Enter Document %d: ", i + 1);
                    fgets(documents[i], sizeof(documents[i]),stdin);

                    size_t len = strlen(documents[i]);

                    if(len > 0 && documents[i][len - 1] == '\n'){
                        documents[i][len-1] = '\0';
                    }
                    else if(strchr(documents[i],'\n') == NULL){
                        printf("Document too long.\n");
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        i--;
                    }
                }
                check_set = 1;
                printf("Documents set successfully.\n");
            }
            else{
                printf("Invalid number of documents. Must be from 1 to 50.\n");
            }
        }
        else if(strcmp(command,"normalize") == 0){
            if(check_set == 1){
                normalize_case_all(documents,doc_num);
                for(int i = 0; i < doc_num; i++){
                    printf("Document %d. %s\n",i+1,documents[i]);
                }
                printf("Documents normalized.\n");
            }
            else{
                printf("No documents set. Use 'set' command first.\n");
            }
        }
        else if(strcmp(command,"tokenize") == 0){
            if(check_set == 1){
                tokenize_all(documents,doc_num,tokens);
                printf("Tokens:\n");
                for(int i = 0; i < token_count; i++){
                    printf("%d. %s\n",i+1,tokens[i]);
                }
                printf("Tokenization complete. Total tokens: %d",token_count);
                check_token = 1;
            }
            else{
                printf("No documents set. Use 'set' command first.\n");
            }
        }
        else if(strcmp(command,"remove_stop") == 0){
            if(check_set == 1 && check_token == 1){
                remove_stop_words_all(tokens,stop_words,tokens_except_stop_words);
                printf("Tokens after stop-word removal:\n");
                for(int i = 0; i < token_exc_stp_count; i++){
                    printf("%d. %s\n",i+1,tokens_except_stop_words[i]);
                }
                printf("Stop-word removal complete. Tokens remaining: %d",token_exc_stp_count);
            }
            else if(check_set != 1){
                printf("No documents set. Use 'set' command first.\n");
            }
            else if(check_token != 1){
                printf("No tokens available. Use 'tokenize' command first.\n");
            }
        }
        else if(strcmp(command,"stem") == 0){
            if(check_set == 1 && check_token == 1){
                stem_all_tokens(tokens_except_stop_words,stemmed_tokens);
                printf("Stemmed Tokens:\n");
                for(int i = 0; i < token_exc_stp_count; i++){
                    printf("%d. %s\n",i+1,stemmed_tokens[i]);
                }
                printf("Stemming complete. Total stemmed tokens: %d",token_exc_stp_count);
            }
            else if(check_set != 1){
                printf("No documents set. Use 'set' command first.\n");
            }
            else if(check_token != 1){
                printf("No tokens available. Use 'tokenize' command first.\n");
            }
        }
        else if(strcmp(command,"tf") == 0){
            if(check_set == 1 && check_token == 1){
                char word[MAX_TOKEN_LEN];
                printf("Enter word to compute TF: ");
                scanf("%s",word);
                //char word[], int doc_id, char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]
                for(int i = 0; i < doc_num; i++){
                    printf("Document %d: %.4lf\n", i + 1, compute_tf(word, i, documents, stop_words));
                }
            }
            else if(check_set != 1){
                printf("No documents set. Use 'set' command first.\n");
            }
            else if(check_token != 1){
                printf("No tokens available. Use 'tokenize' command first.\n");
            }
        }
        else if(strcmp(command,"idf") == 0){
            if(check_set == 1 && check_token == 1){
                char word[MAX_TOKEN_LEN];
                printf("Enter word to compute IDF: ");
                scanf("%s",word);
                //char word[], int doc_id, char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]
                printf("IDF for '%s': %0.4lf\n",word,compute_idf(word,doc_num,documents,stop_words));
            }
            else if(check_set != 1){
                printf("No documents set. Use 'set' command first.\n");
            }
            else if(check_token != 1){
                printf("No tokens available. Use 'tokenize' command first.\n");
            }
        }
        else if(strcmp(command,"tfidf") == 0){
            if(check_set == 1 && check_token == 1){
                char word[MAX_TOKEN_LEN];
                printf("Enter word to compute TF-IDF: ");
                scanf("%s",word);
                //char word[], int doc_id, char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]
                compute_tfidf_all(word,doc_num,documents,stop_words);
            }
            else if(check_set != 1){
                printf("No documents set. Use 'set' command first.\n");
            }
            else if(check_token != 1){
                printf("No tokens available. Use 'tokenize' command first.\n");
            }
        }
        else if(strcmp(command,"help") == 0){
            printf("\n  ");
            printf("set          - Prompt for the number of documents and their text.\n  ");
            printf("normalize    - Convert all documents to lowercase and display them.\n  ");
            printf("tokenize     - Tokenize all documents into words and display the tokens.\n  ");
            printf("remove_stop  - Remove stop words from tokens and display the filtered tokens.\n  ");
            printf("stem         - Apply simple stemming (remove suffixes like \"ing\",\"ed\",\"s\") and display results.\n  ");
            printf("tf           - Compute and display Term Frquency for a specified word across documents.\n  ");
            printf("idf          - Compute and display Inverse Document Frequency for a specified word.\n  ");
            printf("tfidf        - Compute and display TF-IDF scores for a specified word across documents.\n  ");
            printf("help         - Print the list of all available commands.\n  ");
            printf("stat         - Display TF,IDF, and TF-IDF for all tokens across all documents in a matrix format.\n  ");
            printf("exit         - Exit the program\n");
        }
        else if(strcmp(command,"stat") == 0){
            if(check_set == 1 && check_token == 1){
                //char word[], int doc_id, char docs[][MAX_LEN],char stp_wrd[][MAX_TOKEN_LEN]
                display_stat(stemmed_tokens,doc_num,documents,stop_words);
            }
            else if(check_set != 1){
                printf("No documents set. Use 'set' command first.\n");
            }
            else if(check_token != 1){
                printf("No tokens available. Use 'tokenize' command first.\n");
            }
        }
        else if(strcmp(command,"exit") == 0){
            printf("Exiting program.\n");
            break;
        }
        else{
            printf("Unknown Command. Type 'help' for list of commands.\n");
        }
    }
}
