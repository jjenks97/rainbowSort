#include "IRremote.h"
#include "FastLED.h"

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define NUM_LEDS 297
  
CRGB leds[NUM_LEDS]; 

int *ledSort;

int ledSortSize;



#define DATA_PIN 6







void setup() {
  Serial.begin(9600);
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  Serial.println("setup");
  irrecv.enableIRIn();
  irrecv.blink13(true);
  FastLED.setBrightness(100);
  fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
  FastLED.show();
}

void loop() {

  FastLED.clear();
  
  for (int i = 0; i < NUM_LEDS; i++){
    
    leds[i].setHue(rand()%256);
    FastLED.show();
    delay(15);
  }
  delay(5000);
  rainbowSortRGB();
  delay(15000);






  
  
//  if (irrecv.decode(&results)){
//    switch(results.value) {
//      case 0xFFA25D: //pwr
//      if(NUM_LEDS > 200) {
//        ledSortSize = 200;
//        ledSort = new int[ledSortSize];
//      }
//      else {
//        ledSort = new int[NUM_LEDS];
//        ledSortSize = NUM_LEDS;
//      }
//      FastLED.clear();
//      delay(100);
//      for (int i = 0; i < ledSortSize; i++){
//        ledSort[i] = rand()%256;
//        leds[i].setHue(ledSort[i]);
//        FastLED.show();
//        delay(15);
//      }
//      Serial.println(F("rainbow"));
//      
//      
//
//      break;
//      case 0xFF6897:
//      FastLED.clear();
//      delay(100);
//      delete[]ledSort;
//      for (int i = 0; i < NUM_LEDS; i++){
//        leds[i].setHue(rand()%256);
//        FastLED.show();
//        delay(15);
//      }
//      rainbowSortRGB();
//      break;
//      case 0xFFE21D: //FUNC
//      fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
//      break;
//      case 0xFF30CF: //1
//      Serial.println(F("bubble start"));
//      bubbleSortHue(ledSort, ledSortSize);
//      Serial.println(F("bubble done"));
//      break;
//      case 0xFF18E7: //2
//      Serial.println(F("inserstion start"));
//      insertionSortHue(ledSort, ledSortSize);
//      Serial.println(F("insertion done"));
//
////      Serial.println("heapsort start");
////      heapSortHue(ledSort, ledSortSize); //crashes if array is too large
////      Serial.println("heapsort done");
//      break;
//      case 0xFF7A85: //3
//      Serial.println(F("quicksort start"));
//      quickSortHue(ledSort, 0, ledSortSize -1);
//      Serial.println(F("quicksort done"));
//      break;
//
//      case 0xFF10EF: //4
//      if (NUM_LEDS > ledSortSize) {
//        while((ledSortSize*4 + NUM_LEDS*3) > 1450){
//          ledSortSize--;
//        }
//        delete[]ledSort;
//        ledSort = new int[ledSortSize];
//        FastLED.clear();
//        for (int i = 0; i < ledSortSize; i++){
//          ledSort[i] = rand()%256;
//          leds[i].setHue(ledSort[i]);
//          FastLED.show();
//          delay(15);
//        }
//      }
//      Serial.println(F("mergeSort start"));
//      mergeSortHue(ledSort, 0, ledSortSize -1);
//      Serial.println(F("mergeSort done"));
//      break;
//           
//
//      
//    }
//    irrecv.resume();
//  }
//
//  FastLED.show();
//  delay(275);
  

}

void rainbowSortRGB() {
  Serial.println(F("rainbowSortRGB"));
  
  

  
    heapSortRed(leds, NUM_LEDS);
    Serial.println(F("red sorted"));

    heapSortBlue(leds, NUM_LEDS);
    Serial.println(F("blue sorted"));

     
    int blueEndpoint = 0;
    while(leds[blueEndpoint].b > 0 and blueEndpoint < NUM_LEDS) {
      blueEndpoint++;

    }
    
    heapSortGreen(leds, blueEndpoint);
    Serial.println(F("green1 sorted"));

    


    
    
    
    

    int redEndpoint = 0;
    while (leds[redEndpoint].r > 0 and redEndpoint < NUM_LEDS){
      redEndpoint++;
    }
    heapSortRed2(leds, redEndpoint);
    Serial.println(F("red2 sorted"));
    

    
    //heapSortGreen2(leds,blueEndpoint, NUM_LEDS);
    quickSortGreen2(leds, blueEndpoint, NUM_LEDS);
    Serial.println(F("green2 sorted"));

    
    //quickSortRed3(leds, blueEndpoint, NUM_LEDS);
    
    
    for (int i = 0; i < NUM_LEDS; i++){
      
//     Serial.print(i);
//      Serial.print(" ");
//      Serial.print(leds[i].r);
//      Serial.print(" ");
//      Serial.print(leds[i].g);
//      Serial.print(" ");
//      Serial.print(leds[i].b);
//      Serial.println("");
//    }
//    Serial.println(F("done"));

  

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
      swapRGB(leds, i, j);
      
    }
  }
  swapRGB(leds, i + 1, high);
  
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
      swapRGB(leds, i, j);
      
    }
  }
  swapRGB(leds, i + 1, high);
  
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
    if(leds[j].g > pivot)
    {
      i++;
      swapRGB(leds, i, j);
      
    }
  }
  swapRGB(leds, i + 1, high);
  
  return (i + 1);
}

void quickSortRed3(CRGB leds[], int low, int high) {
  
  if(low < high) {
    int pi = partitionGreen2(leds, low, high);

    quickSortGreen2(leds, low, pi - 1);
    quickSortGreen2(leds, pi + 1, high);
  }
  
  
}

int partitionRed3(CRGB leds[], int low, int high)
{
  int pivot = leds[high].r;
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++)
  {
    if(leds[j].r < pivot)
    {
      i++;
      swapRGB(leds, i, j);
      
    }
  }
  swapRGB(leds, i + 1, high);
  
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
      swapRGB(leds, i, j);
      
    }
  }
  swapRGB(leds, i + 1, high);
  
  return (i + 1);
}
void swapRGB(CRGB leds[], int x, int y) {
  uint8_t r = leds[x].r;
  uint8_t g = leds[x].g;
  uint8_t b = leds[x].b;
  uint8_t r2 = leds[y].r;
  uint8_t g2 = leds[y].g;
  uint8_t b2 = leds[y].b;
  leds[y].setRGB(r,g,b);
  leds[x].setRGB(r2,g2,b2);
  
  FastLED.show();
  //delay(25);
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
      swapRGB(leds, i, j);
      
    }
  }
  swapRGB(leds, i + 1, high);
  
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
        swapRGB(leds, i, largest); 
  
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
        swapRGB(leds, 0, i); 
  
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
        swapRGB(leds, i, largest); 
  
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
        swapRGB(leds, 0, i); 
  
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
        swapRGB(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyRed2(leds, n, largest); 
    } 
} 
  

void heapSortRed2(CRGB leds[], int n) 
{ 
     
    for (int i = n - 1; i >= 0; i--) 
        heapifyRed2(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swapRGB(leds, 0, i); 
  
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
        swapRGB(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyGreen(leds, n, largest); 
    } 
} 
  

void heapSortGreen(CRGB leds[], int n) 
{ 
     
    for (int i = n - 1; i >= 0; i--) 
        heapifyGreen(leds, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swapRGB(leds, 0, i); 
  
        // call max heapify on the reduced heap 
        heapifyGreen(leds, i, 0); 
    } 
}

void heapifyGreen2(CRGB leds[], int n, int i, int x, int blueEnd) 
{    
    int largest = i; // Initialize largest as root 
    int l = 2*x + 1; // left = 2*i + 1 
    int r = 2*x + 2; // right = 2*i + 2
    int largest2; 
  
    // If left child is larger than root 
    if (l < n && leds[l + blueEnd].g < leds[largest].g) 
        largest = l + blueEnd;
        largest2 = l; 
  
    // If right child is larger than largest so far 
    if (r < n && leds[r + blueEnd].g < leds[largest].g) 
        largest = r + blueEnd;
        largest2 = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swapRGB(leds, i, largest); 
  
        // Recursively heapify the affected sub-tree 
        heapifyGreen2(leds, n, largest, largest2, blueEnd); 
    } 
} 
  

void heapSortGreen2(CRGB leds[],int blueEnd, int n) 
{  
    int x = n - blueEnd - 1;
    for (int i = n - 1; i >= blueEnd; i--, x--) {
        heapifyGreen2(leds, n - blueEnd, i, x, blueEnd); 
    }
    x = n - blueEnd - 1;
    // One by one extract an element from heap 
    for (int i=n-1; i >= blueEnd; i--, x--) 
    { 
        // Move current root to end 
        swapRGB(leds, blueEnd, i); 
  
        // call max heapify on the reduced heap 
        heapifyGreen2(leds, x, blueEnd, 0, blueEnd); 
    } 
} 

void bubbleSortCleanupRed2(CRGB leds[], int n){
  int i, j;
  for(i = 0; i < n - 1; i++){
    for (j = 0; j < n - i - 1; j++){
      if (leds[j].r < leds[j + 1].r){
        swapRGB(leds, j, j + 1);
      }
    }
  }
}
void bubbleSortCleanupRed(CRGB leds[], int n){
  int i, j;
  for(i = 0; i < n - 1; i++){
    for (j = (NUM_LEDS*5)/6; j < n - i - 1; j++){
      if (leds[j].b > leds[j + 1].b){
        swapRGB(leds, j, j + 1);
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








void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp;
    for(int i = 0; i < ledSortSize; i++){
      leds[i].setHue(ledSort[i]); 
    }
    FastLED.show();
    delay(50);
} 




void bubbleSortHue(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 
  
// main function to do heap sort 
void heapSortHue(int arr[], int n) 
{ 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(arr[0], arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
} 


void insertionSortHue(int arr[], int n) 
{ 
   int i, key, j; 
   for (i = 1; i < n; i++) 
   { 
       key = arr[i]; 
       j = i-1; 
  
       /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
       while (j >= 0 && arr[j] > key) 
       { 
           arr[j+1] = arr[j]; 
           j = j-1; 
           for(int i = 0; i < ledSortSize; i++){
              leds[i].setHue(ledSort[i]); 
            }
            FastLED.show();
            delay(50);
       } 
       arr[j+1] = key; 
       for(int i = 0; i < ledSortSize; i++){
              leds[i].setHue(ledSort[i]); 
            }
            FastLED.show();
            
   } 
} 


int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSortHue(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSortHue(arr, low, pi - 1);
        quickSortHue(arr, pi + 1, high);
    }
}



void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            leds[k].setHue(arr[k]);
            FastLED.show();
            delay(30);
            i++; 
        } 
        else
        { 
            arr[k] = R[j];
            leds[k].setHue(arr[k]);
            FastLED.show();
            delay(30); 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i];
        leds[k].setHue(arr[k]);
        FastLED.show();
        delay(30); 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j];
        leds[k].setHue(arr[k]);
        FastLED.show();
        delay(30); 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSortHue(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSortHue(arr, l, m); 
        mergeSortHue(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
}  
