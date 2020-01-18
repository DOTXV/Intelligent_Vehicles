#include <stdio.h>
#include <assert.h>

float t;           // tao
int MAX_MESSAGES;  // lines

typedef struct message {
    int Priority;
    float TransmissionTime;
    int Period;
}Message;
Message *messages;

int floor(float num) {
    if((int)num < num)
        num++;
    return (int)num;
}

float get_Q(float B, float Q, int i) {
    float RHS = B;
    for(int j = 0; j < MAX_MESSAGES; j++)
        if(messages[i].Priority > messages[j].Priority)
            RHS += floor(((float)Q + t)/(float)messages[j].Period) * messages[j].TransmissionTime;

    if(RHS == Q)
        return RHS;
    return get_Q(B, RHS, i);
}

float get_B(int i) {
    float result = messages[i].TransmissionTime;
    for(int j = i; j < MAX_MESSAGES; j++){
        //if(messages[i].Priority < messages[j].Priority)
        if(result < messages[j].TransmissionTime)  
            result = messages[j].TransmissionTime;
    }
    return result;
}

int main() {
    FILE *fPtr;

    fPtr = fopen("Input.dat", "r");
    assert(fPtr != NULL);

    fscanf(fPtr, "%d%f", &MAX_MESSAGES, &t);

    messages = new Message[MAX_MESSAGES];
    for(int j = 0; j < MAX_MESSAGES; j++) {
        fscanf(fPtr, "%d", &((messages + j)->Priority));
        fscanf(fPtr, "%f", &((messages + j)->TransmissionTime));
        fscanf(fPtr, "%d", &((messages + j)->Period));
    }
    
    for(int i = 0; i < MAX_MESSAGES; i++)
        printf("%.2f\n", messages[i].TransmissionTime + get_Q(get_B(i), get_B(i), i));
    return 0;
}
