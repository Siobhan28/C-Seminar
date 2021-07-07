#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>         //true and false 
#define capacity_of_Points 2

//-------------------------------------

	// Structures

//-------------------------------------

        //-------------------------------------

	        // Point Structure

    	//-------------------------------------

 struct Point{
    float x;                                                    //x value of the point 
    float y;                                                    //y value of the point

};
typedef struct Point point_t;                             

        //-------------------------------------

	        // Rectangle Structure

    	//-------------------------------------


struct Rectangle{
    point_t point;                                                       //center point (x/y)   w/2 and h/2 
    
    float width; 

    float height; 

};
typedef struct Rectangle rectangle_t; 

        //-------------------------------------

	        // QuadTree Node

    	//-------------------------------------


 struct QuadTree{
    //the boundary of the node
    rectangle_t boundary;                                        // centerX, centerY and width and height 

    
    point_t points[capacity_of_Points];                          //max capacity of points in the Quadtree

    int n_points;                                                // number of points in quadtree

    //childrenNodes
    struct QuadTree *northWest;                                 //creates the children of the parentQuadTree 
    struct QuadTree *northEast; 
    struct QuadTree *southWest; 
    struct QuadTree *southEast; 

};
typedef struct QuadTree QTree_t; 

//-------------------------------------

	//DECLARATION OF FUNCTIONS

//-------------------------------------

QTree_t *createQuadtree(float centerX, float centerY, float width, float height);

void subdivideNode(QTree_t* parentNode);

void insertThePoint(QTree_t *quadTree, point_t point);


//not yet implemented
/*
 void QueryRange(rectangle_t range);

void delete(point_t point);
*/

//-------------------------------------

	// Main Funktion 

//-------------------------------------



int main(int argc, char **argv){

QTree_t *tree = createQuadtree(0,0,200,200);                   

printf("A\n\n");
insertThePoint(tree,(point_t) {-60, 57});

printf("\nB\n\n");
insertThePoint(tree,(point_t) {60, 15});

printf("\nC\n\n");
insertThePoint(tree,(point_t) {-40, 80});

printf("\nD\n\n");
insertThePoint(tree,(point_t) {10, -10});

printf("\nE\n\n");
insertThePoint(tree,(point_t) {-90, 90});

printf("\nF\n\n");
insertThePoint(tree,(point_t) {-45, 45});
    
    


return 0; 
}





//-------------------------------------

	// FUNCTIONS

//-------------------------------------

QTree_t *createQuadtree(float centerX, float centerY, float width, float height){
    QTree_t* result = malloc(sizeof(QTree_t));
    if(result == NULL){
        printf("Malloc returns NULL. \n EXIT! \n");
        exit (1); 
    }

    result->northWest = NULL;               //no childrennodes yet 
    result->northEast = NULL; 
    result->southWest = NULL; 
    result->southEast = NULL; 

    result->n_points = 0; 

    result->boundary.height = height; 
    result->boundary.width = width; 
    result->boundary.point.x = centerX; 
    result->boundary.point.y = centerY; 


    return result; 

}


void insertThePoint(QTree_t *quadTree, point_t point){

    
    float cx = quadTree->boundary.point.x; 
    
    float cy = quadTree->boundary.point.y; 

    float w = quadTree->boundary.width; 

    float h = quadTree->boundary.height;

    printf("%.2f %.2f %.2f %.2f \n", cx, cy,w, h);

    //fist check if point is within the boundary of the Quadtree
    //if not --> not gonna be inserted 
    if(!(point.x >= cx - w/2 && point.x <= cx + w/2 && point.y >= cy - h/2 && point.y <= cy + h/2)){
        printf("Error! The Point is not in the Boundary of the Quadtree! \n");
        exit(1); 
    }

    
    if(quadTree->n_points < capacity_of_Points){

        printf("direct adding to tree\n");
        quadTree->points[quadTree->n_points++] = point; 

    }else{
        if(quadTree->northEast == NULL){
            printf("node will be subdivided...\n");
            subdivideNode(quadTree);
        }
        int positiveX = point.x - cx >= 0; 
        int positiveY = point.y - cy >= 0; 

        if(positiveX){
            if(positiveY){
                printf("Point in northEast\n");
               //  quadTree->northEast; 
                insertThePoint(quadTree->northEast, point);
            }else{
                printf("Point in southEast\n");
               // quadTree->southEast; 
                insertThePoint(quadTree->southEast, point);
            }
        }else{
             if(positiveY){
                 printf("Point in northWest\n");
               //  quadTree->northWest;
                 insertThePoint(quadTree->northWest, point);
            }else{
                printf("Point in southWest\n");
               // quadTree->southWest;
                insertThePoint(quadTree->southWest, point);
            }
        }
        
    }
    
}


void subdivideNode(QTree_t* parentNode){

    float centerX = parentNode->boundary.point.x;
    float centerY = parentNode->boundary.point.y; 
    float width = parentNode->boundary.width; 
    float height = parentNode->boundary.height; 
    
    float halfWidth = width/2; 
    float halfHeight = height/2; 

    float quaterWidth = width/4;   
    float quaterHeight = height/4; 

    // boundary: x - w/4 , y - h/2 , w/2 , h/2
    // boundary: x + w/4 , y - h/2 , w/2 , h/2
    // boundary: x - w/4 , y + h/2 , w/2 , h/2
    // boundary: x + w/4 , y + h/2 , w/2 , h/2

    parentNode->northWest = createQuadtree(centerX - quaterWidth, centerY + quaterHeight, halfWidth, halfHeight);
    parentNode->northEast = createQuadtree(centerX + quaterWidth, centerY + quaterHeight, halfWidth, halfHeight);
    parentNode->southWest = createQuadtree(centerX - quaterWidth, centerY - quaterHeight, halfWidth, halfHeight);
    parentNode->southEast = createQuadtree(centerX + quaterWidth, centerY - quaterHeight, halfWidth, halfHeight);

}


/*
void QueryRange(rectangle_t range){

    //finds all the points in a certain range

    //if the boundary is not intersecting the quad --> stops 

}

*/



