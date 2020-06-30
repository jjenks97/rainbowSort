#include "IRremote.h"
#include "FastLED.h"

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define NUM_LEDS 100   
  
CRGB leds[NUM_LEDS]; 




#define DATA_PIN 6

int lightArray[256];

struct color {
  int r;
  int g;
  int b;
};
typedef struct color Color;

int brightness = 64;


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  Serial.println("Test");
  irrecv.enableIRIn();
  irrecv.blink13(true);
  FastLED.setBrightness(brightness);
  //fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
  FastLED.show();

}

void loop() {
  if (irrecv.decode(&results)){
    switch(results.value) {
      case 0xFFA25D:
      FastLED.clear();
      
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++){
            leds[i].setHue(rand()% 256);
            FastLED.show();
            delay(15);
      }
      delay(1000);
      masterQuickSort();
      
      
      FastLED.show();

      break;
      case 0xFF6897:
      FastLED.clear();
      Serial.println("rainbow sort");
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++){
            leds[i].setHue(rand()% 256);
            FastLED.show();
            delay(15);
      }
      
      delay(1000);
      
      rainbowSort();
//      case 0xFFE21D: //FUNC
//      FastLED.clear();
//      delay(100);
//      for (int i = 1; i < NUM_LEDS; i++){
//            leds[i].setHue(rand()% 256);
//            FastLED.show();
//            delay(15);
//      }
//      delay(1000);
//      bubbleSort(leds, NUM_LEDS);
//      break;

      
    }
    irrecv.resume();
  }

  FastLED.show();
  delay(500);
  

}

void rainbowSort() {
  
  
  int n = sizeof(leds)/sizeof(leds[0]);
  int n2 = (sizeof(leds)/2)/sizeof(leds[0]);

  int n3 = (sizeof(leds)/3)/sizeof(leds[0]);
  
    heapSortRed(leds, n);
    Serial.println("red sorted");
    heapSortBlue(leds, n);
    Serial.println("blue sorted");

    ;
    heapSortGreen(leds, n2);
    Serial.println("green1 sorted");
    


    quickSortGreen2(leds, NUM_LEDS/2, NUM_LEDS);
    
    Serial.println("green2 sorted");
    heapSortRed2(leds, NUM_LEDS/3);
    Serial.println("red2 sorted");
    
    bubbleSortCleanupRed2(leds, NUM_LEDS/2);
    Serial.println("red2 cleanup done");
    bubbleSortCleanupRed(leds, NUM_LEDS);
   // insertionSortCleanupRed2(leds, NUM_LEDS/2);
    Serial.println("red1 cleanup done");
    
  //heapSortGreen2(leds, NUM_LEDS/2);
//  Serial.println("green2 sorted");

  FastLED.show();
}
void masterQuickSort(){
  quickSortRed(leds, 0, NUM_LEDS - 1);
  Serial.println("red sorted");
  quickSortBlue(leds, 0, NUM_LEDS - 1);
  Serial.println("blue sorted");
  quickSortRed2(leds, 0, (NUM_LEDS/2)-1);
  Serial.println("red2 sorted");
  quickSortGreen1(leds, 0, (NUM_LEDS/2) - 1);
  Serial.println("green1 sorted");
  quickSortGreen2(leds, NUM_LEDS/2, NUM_LEDS);
  Serial.println("green2 sorted");
//  quickSortRed3(leds, NUM_LEDS/2, NUM_LEDS);
//  Serial.println("red3 sorted");
  FastLED.show();
}

void quickSortBlue(CRGB leds[], int low, int high) {
  
  if(low < high) {
    int pi = partitionBlue(leds, low, high);

    quickSortBlue(leds, low, pi - 1);
    quickSortBlue(leds, pi + 1, high);
  }
  
  
}

int partitionBlue (CRGB leds[], int low, int high)
{
  int pivot = leds[high].b;
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++)
  {
    if(leds[j].b >= pivot)
    {
      i++;
      swap(leds, i, j);
      
    }
  }
  swap(leds, i + 1, high);
  
  return (i + 1);
}
void quickSortRed2(CRGB leds[], int low, int high) {
  
  if(low < high) {
    int pi = partitionRed2(leds, low, high);

    quickSortRed2(leds, low, pi - 1);
    quickSortRed2(leds, pi + 1, high);
  }
  
 
}

int partitionRed2 (CRGB leds[], int low, int high)
{
  int pivot = leds[high].r;
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++)
  {
    if(leds[j].r >= pivot)
    {
      i++;
      swap(leds, i, j);
      
    }
  }
  swap(leds, i + 1, high);
  
  return (i + 1);
}
void quickSortGreen2(CRGB leds[], int low, int high) {
  
  if(low < high) {
    int pi = partitionGreen2(leds, low, high);

    quickSortGreen2(leds, low, pi - 1);
    quickSortGreen2(leds, pi + 1, high);
  }
  
  
}

int partitionGreen2 (CRGB leds[], int low, int high)
{
  int pivot = leds[high].g;
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++)
  {
    if(leds[j].g >= pivot)
    {
      i++;
      swap(leds, i, j);
      
    }
  }
  swap(leds, i + 1, high);
  
  return (i + 1);
}
void quickSortRed(CRGB leds[], int low, int high) {
  
  if(low < high) {
    int pi = partitionRed(leds, low, high);

    quickSortRed(leds, low, pi - 1);
    quickSortRed(leds, pi + 1, high);
  }
  
  
}
void quickSortGreen1(CRGB leds[], int low, int high) {
  
  if(low < high) {
    int pi = partitionGreen1(leds, low, high);

    quickSortGreen1(leds, low, pi - 1);
    quickSortGreen1(leds, pi + 1, high);
  }
  
  
}

int partitionGreen1 (CRGB leds[], int low, int high)
{
  int pivot = leds[high].g;
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++)
  {
    if(leds[j].g <= pivot)
    {
      i++;
      swap(leds, i, j);
      
    }
  }
  swap(leds, i + 1, high);
  
  return (i + 1);
}
void swap(CRGB leds[], int x, int y) {
  int r = leds[x].r;
  int g = leds[x].g;
  int b = leds[x].b;
  int r2 = leds[y].r;
  int g2 = leds[y].g;
  int b2 = leds[y].b;
  leds[y].setRGB(r,g,b);
  leds[x].setRGB(r2,g2,b2);
  
  FastLED.show();
  delay(25);
}

int partitionRed (CRGB leds[], int low, int high)
{
  int pivot = leds[high].r;
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++)
  {
    if(leds[j].r <= pivot)
    {
      i++;
      swap(leds, i, j);
      
    }
  }
  swap(leds, i + 1, high);
  
  return (i + 1);
}





void heapifyRed(CRGB leds[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && leds[l].r > leds[largest].r) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && leds[r].r > leds[largest].r) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyRed(leds, n, largest); 
    } 
} 
  

void heapSortRed(CRGB leds[], int n) 
{ 
     
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapifyRed(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(leds, 0, i); 
  
        // call max heapify on the reduced heap 
        heapifyRed(leds, i, 0); 
    } 
} 

void heapifyBlue(CRGB leds[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && leds[l].b < leds[largest].b) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && leds[r].b < leds[largest].b) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyBlue(leds, n, largest); 
    } 
} 
  

void heapSortBlue(CRGB leds[], int n) 
{ 
     
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapifyBlue(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(leds, 0, i); 
  
        // call max heapify on the reduced heap 
        heapifyBlue(leds, i, 0); 
    } 
} 



void heapifyRed2(CRGB leds[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && leds[l].r < leds[largest].r) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && leds[r].r < leds[largest].r) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyRed2(leds, n, largest); 
    } 
} 
  

void heapSortRed2(CRGB leds[], int n) 
{ 
     
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapifyRed2(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(leds, 0, i); 
  
        // call max heapify on the reduced heap 
        heapifyRed2(leds, i, 0); 
    } 
} 

void heapifyGreen(CRGB leds[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && leds[l].g > leds[largest].g) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && leds[r].g > leds[largest].g) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyGreen(leds, n, largest); 
    } 
} 
  

void heapSortGreen(CRGB leds[], int n) 
{ 
     
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapifyGreen(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(leds, 0, i); 
  
        // call max heapify on the reduced heap 
        heapifyGreen(leds, i, 0); 
    } 
}

void heapifyGreen2(CRGB leds[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && leds[l].g < leds[largest].g) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && leds[r].g < leds[largest].g) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyGreen2(leds, n, largest); 
    } 
} 
  

void heapSortGreen2(CRGB leds[], int n) 
{ 
     
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapifyGreen2(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(leds, 0, i); 
  
        // call max heapify on the reduced heap 
        heapifyGreen2(leds, i, 0); 
    } 
} 

void bubbleSortCleanupRed2(CRGB leds[], int n){
  int i, j;
  for(i = 0; i < n - 1; i++){
    for (j = 0; j < n - i - 1; j++){
      if (leds[j].r < leds[j + 1].r){
        swap(leds, j, j + 1);
      }
    }
  }
}
void bubbleSortCleanupRed(CRGB leds[], int n){
  int i, j;
  for(i = 0; i < n - 1; i++){
    for (j = (NUM_LEDS*3)/4; j < n - i - 1; j++){
      if (leds[j].b > leds[j + 1].b){
        swap(leds, j, j + 1);
      }
    }
  }
}

//void insertionSortCleanupRed2(CRGB leds[], int n){
//  int i;
//  int j;
//  int key;
//  for(i = 1; i < n; i++)
//  {
//    key = leds[i].r;
//    j = i - 1;
//  }
//  while (j >= 0 && leds[j].r < key){
//    int x = leds[j].r;
//    leds[j+1].red = x;
//    j = j-1;
//    delay(25);
//  }
//  leds[j+1].red = key;
//  delay(25);
//}
 
void setColor(Color *c, int r, int g, int b) {
  c->r = r;
  c->g = g;
  c->b = b;
}
