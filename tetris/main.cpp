#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#define MATRIX_ROWS 21
#define MATRIX_COLS 16

int level,steps_time,length_unit,score,window_width,window_height,elapsed_time;
struct RECTANGLE{
    int left,right,top,bottom;
};
/**
Tetris Shapes (values in matrix)
0--empty
1--T
2--L
3--Z
4--I
5--O
*/

/**
Game States
1--main menu
2--game screen
3--settings screen
4-top score screen
*/
void GameSettings()
{
    level=0;
    steps_time=300;
    length_unit=30;
    score=0;
    window_width=700;
    window_height=700;
    elapsed_time=0;
    setSpeed();
}

class States
{
private:
    int state;
public:
    States()
    {
        state=1;
    }
    void setState(int s)
    {
        state=s;
    }
    int getState()
    {
        return state;
    }
} current_state;

class Paint
{
private:
    char string [100];
    int menu_number;
    int menu_items_count;
    GLuint texture_id[20];
public:
    Paint()
    {
        menu_number=1;
        menu_items_count=4;
    }
    void setNextMenuItem();
    void setPrevMenuItem();
    int getMenuItemPos();
    GLuint LoadTexture(char *FileName );
    void DrawBackgroundImage();
    void LoadAllTextures();
    void DrawRectangle(RECTANGLE rect);
    void drawText(char*string,int x,int y, float font_size);
    void printMessageEsc();
    void printMessageGameOver();
    void DrawTexturedRectangle(RECTANGLE rectangle,int item_number);
    void DrawGameMenu();
    void DrawGameSubwindows();
} paint_background;

void Paint::setNextMenuItem()
{
    if(menu_number==menu_items_count)
        menu_number =1;
    else
        menu_number++;
}
void Paint::setPrevMenuItem()
{
    if(menu_number==1)
        menu_number=menu_items_count;
    else
        menu_number--;
}
int Paint::getMenuItemPos()
{
    return menu_number;
}
void Paint::DrawTexturedRectangle(RECTANGLE rectangle,int item_number)
{
    switch(item_number)
    {
    case 1:
        if(menu_number == 1)
            glBindTexture(GL_TEXTURE_2D, texture_id[2]);
        else
            glBindTexture(GL_TEXTURE_2D, texture_id[3]);
        break;
    case 2:
        if(menu_number == 2)
            glBindTexture(GL_TEXTURE_2D, texture_id[4]);
        else
            glBindTexture(GL_TEXTURE_2D, texture_id[5]);
        break;
    case 3:
        if(menu_number == 3)
            glBindTexture(GL_TEXTURE_2D, texture_id[6]);
        else
            glBindTexture(GL_TEXTURE_2D, texture_id[7]);
        break;
    case 4:
        if(menu_number == 4)
            glBindTexture(GL_TEXTURE_2D, texture_id[8]);
        else
            glBindTexture(GL_TEXTURE_2D, texture_id[9]);
        break;
    case 5:
        glBindTexture(GL_TEXTURE_2D, texture_id[10]);
        break;
    case 6:
        glBindTexture(GL_TEXTURE_2D, texture_id[11]);
        break;
    case 7:
        glBindTexture(GL_TEXTURE_2D, texture_id[12]);
        break;
    case 8:
        glBindTexture(GL_TEXTURE_2D, texture_id[13]);
        break;
    case 9:
        glBindTexture(GL_TEXTURE_2D, texture_id[14]);
        break;
    default:
        glBindTexture(GL_TEXTURE_2D, NULL);
        break;
    }
//to draw a rectangle
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);
    glVertex2f(rectangle.left,rectangle.bottom );
    glTexCoord2f(1.0f,0.0f);
    glVertex2f(rectangle.right,rectangle.bottom);
    glTexCoord2f(1.0f,1.0f);
    glVertex2f(rectangle.right,rectangle.top );
    glTexCoord2f(0.0f,1.0f);
    glVertex2f(rectangle.left,rectangle.top);
    glEnd();
}
void DrawGameSubwindows()
{
    int unit=game_settings.getGameRectLength();
// the rectangle which includes the next block shape
    RECTANGLE left_border_up_b= {unit,unit,unit+4*unit,unit+4*unit};
// the rectangle which include the score
    RECTANGLE left_border_down_b= {unit,18*unit,unit+4*unit,18*unit+4*unit};
//the recangle which include the game blocks
    RECTANGLE
    game_screen= {unit+4*unit+unit,unit,6*unit+16*unit,unit+4*unit+13*unit+4*u
                  nit
                 };
//draw
    DrawRectangle(game_screen);
    DrawRectangle(left_border_up_b);
    DrawRectangle(left_border_down_b);
//put text score
    glColor3f(1.0f,1.0f,1.0f);
    sprintf(string,"SCORE %d ",pcResult);
    drawText(string,unit+0.5*unit,18*unit+unit,1.5);
//put the speed text
    sprintf(string,"SPEED %d ",game_settings.getSpeed());
    drawText(string,unit+0.5*unit,18*unit+(1.75)*unit,1.5);
//put level text
    sprintf(string,"LEVEL %d ",game_settings.getLevel());
    drawText(string,unit+0.5*unit,18*unit+(2.5)*unit,1.5);
//put elpsed time
    sprintf(string,"TIME %d ",game_settings.getElapsedTime());
    drawText(string,unit+0.5*unit,18*unit+(3.25)*unit,1.5);
//put the shape text
    drawText("NEXT",unit+unit,unit+unit,2);
//draw the next shape rectangles(block)
    RECTANGLE first_rect;
    RECTANGLE second_rect;
    RECTANGLE third_rect;
    RECTANGLE fourth_rect;
    int next_shape=current_moving_block.getNextshape();
    int hlf=unit/2;
    switch(next_shape)
    {
    case 1:
//T shape
        first_rect.left=unit+hlf;
        first_rect.top=unit+2*unit;
        first_rect.right=2*unit+hlf;
        first_rect.bottom=3*unit+unit;
        second_rect.left=2*unit+hlf;
        second_rect.top=unit+2*unit;
        second_rect.right=3*unit+hlf;
        second_rect.bottom=3*unit+unit;
        third_rect.left=3*unit+hlf;
        third_rect.top=unit+2*unit;
        third_rect.right=4*unit+hlf;
        third_rect.bottom=3*unit+unit;
        fourth_rect.left=2*unit+hlf;
        fourth_rect.top=unit+3*unit;
        fourth_rect.right=3*unit+hlf;
        fourth_rect.bottom=4*unit+unit;
        break;
    case 2:
// L shape
        first_rect.left=unit+hlf;
        first_rect.top=unit+2*unit;
        first_rect.right=2*unit+hlf;
        first_rect.bottom=3*unit+unit;
        second_rect.left=2*unit+hlf;
        second_rect.top=unit+2*unit;
        second_rect.right=3*unit+hlf;
        second_rect.bottom=3*unit+unit;
        third_rect.left=3*unit+hlf;
        third_rect.top=unit+2*unit;
        third_rect.right=4*unit+hlf;
        third_rect.bottom=3*unit+unit;
        fourth_rect.left=unit+hlf;
        fourth_rect.top=unit+3*unit;
        fourth_rect.right=2*unit+hlf;
        fourth_rect.bottom=4*unit+unit;
        break;
    case 3:
//Z shape
        first_rect.left=unit+hlf;
        first_rect.top=unit+3*unit;
        first_rect.right=2*unit+hlf;
        first_rect.bottom=4*unit+unit;
        second_rect.left=2*unit+hlf;
        second_rect.top=unit+2*unit;
        second_rect.right=3*unit+hlf;
        second_rect.bottom=3*unit+unit;
        third_rect.left=3*unit+hlf;
        third_rect.top=unit+2*unit;
        third_rect.right=4*unit+hlf;
        third_rect.bottom=3*unit+unit;
        fourth_rect.left=2*unit+hlf;
        fourth_rect.top=unit+3*unit;
        fourth_rect.right=3*unit+hlf;
        fourth_rect.bottom=4*unit+unit;
        break;
    case 4:
//I shape
        first_rect.left=unit;
        first_rect.top=3*unit;
        first_rect.right=unit+unit;
        first_rect.bottom=3*unit+unit;
        second_rect.left=unit+unit;
        second_rect.top=3*unit;
        second_rect.right=unit+2*unit;
        second_rect.bottom=3*unit+unit;
        third_rect.left=unit+2*unit;
        third_rect.top=3*unit;
        third_rect.right=unit+3*unit;
        third_rect.bottom=3*unit+unit;
        fourth_rect.left=unit+3*unit;
        fourth_rect.top=3*unit;
        fourth_rect.right=unit+4*unit;
        fourth_rect.bottom=3*unit+unit;
        break;
    case 5:
//O shape
        first_rect.left=unit+unit;
        first_rect.top=unit+3*unit;
        first_rect.right=unit+2*unit;
        first_rect.bottom=4*unit+unit;
        second_rect.left=unit+unit;
        second_rect.top=3*unit;
        second_rect.right=unit+2*unit;
        second_rect.bottom=3*unit+unit;
        third_rect.left=unit+2*unit;
        third_rect.top=3*unit;
        third_rect.right=unit+3*unit;
        third_rect.bottom=3*unit+unit;
        fourth_rect.left=unit+2*unit;
        fourth_rect.top=unit+3*unit;
        fourth_rect.right=unit+3*unit;
        fourth_rect.bottom=4*unit+unit;
        break;
    default:
        break;
    }
    DrawTexturedRectangle(first_rect,next_shape+4);
    DrawTexturedRectangle(second_rect,next_shape+4);
    DrawTexturedRectangle(third_rect,next_shape+4);
    DrawTexturedRectangle(fourth_rect,next_shape+4);
}

enum Sides {LEFT,RIGHT,TOP,BOTTOM};

class Block
{
private:
    int row_pos;
    int col_pos;
    int rotation_pos;
    int shape;
    int next_shape;
    bool is_halt_mode;
public:
    Block()
    {
        setNextShape();
        resetBlock();
    }
    int SetRandShape()
    {
        // 1:T, 2:L , 3:Z, 4:I 5:O
        int rand_shape=rand()%5; //output from 0 to 4
        rand_shape++;
        return rand_shape;
    }
    void resetBlock()
    {
        row_pos=0;
        col_pos=7;
        is_halt_mode=false;
        rotation_pos=1;
        shape=next_shape;
        setNextShape();
    }
    void setNextShape()
    {
        next_shape=SetRandShape();
    }
    int getNextshape()
    {
        return next_shape;
    }
    void MoveBottom(bool isDownArrowPressed)
    {
        if(!isCollide(BOTTOM)&& !is_halt_mode)
        {
            row_pos++;
//this way we will increase time
//only if the keydown is not pressed
            if(!isDownArrowPressed)
                game_settings.increaseElapsedTime();
        }
    }
    void MoveRight()
    {
        if(!isCollide(RIGHT)&& !is_halt_mode)
        {
            col_pos++;
            game_settings.increaseElapsedTime();
        }
    }
    void MoveLeft()
    {
        if(!isCollide(LEFT)&& !is_halt_mode)
        {
            col_pos--;
            game_settings.increaseElapsedTime();
        }
    }
    void RotateShape()
    {
        if(!is_halt_mode)
        {
            if(rotation_pos == 4)
                rotation_pos=1;
            else
                rotation_pos++;
        }
    }
    void haltGame()
    {
        is_halt_mode=true;
    }
    void continueGame()
    {
        is_halt_mode=false;
    }
    bool isHaltMode()
    {
        return is_halt_mode;
    }
    int getRow()
    {
        return row_pos;
    }
    int getCol()
    {
        return col_pos;
    }
    int getRotation()
    {
        return rotation_pos;
    }
    int getShape()
    {
        return shape;
    }
    bool isCollide(Sides sd)
    {
        switch(sd)
        {
        case LEFT:
            if(col_pos <= 0 )
            {
                return true;
            }
            break;
        case RIGHT:
            if(col_pos >= MATRIX_COLS-1)
            {
                return true;
            }
            break;
        case BOTTOM:
            if(row_pos >= MATRIX_ROWS-1)
            {
                return true;
            }
            break;
        }
        return false;
    }

}
class GameMatrix
{
private:
    int single_block[MATRIX_ROWS][MATRIX_COLS];
    int block_store[MATRIX_ROWS][MATRIX_COLS];
public:
    GameMatrix()
    {
        ClearSingleBlockMatrix();
        ClearBlockStoreMatrix();
    }
    void ClearSingleBlockMatrix()
    {
        for(int i=0; i<MATRIX_ROWS; i++)
        {
            for(int j=0; j<MATRIX_COLS; j++)
                single_block[i][j]=0;
        }
    }
    void ClearBlockStoreMatrix()
    {
        for(int i=0; i<MATRIX_ROWS; i++)
        {
            for(int j=0; j<MATRIX_COLS; j++)
                block_store[i][j]=0;
        }
    }
    void setSingleBlockElement(int row,int col,int value)
    {
        if(row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS)
            single_block[row][col]=value;
    }
    int getBlockStoreMatrixElement(int i,int j)
    {
        if(i >= 0 && i < MATRIX_ROWS && j >= 0 && j < MATRIX_COLS)
//touch block
            return block_store[i][j];
        else
//touch the walls
            return -1;
    }
    bool isBlockTouchBlock(Sides sd)
    {
        if(sd == BOTTOM)
        {
            for(int i=0; i<MATRIX_ROWS; i++)
            {
                for(int j=0; j<MATRIX_COLS; j++)
                {
                    if(single_block[i][j] > 0)
                    {
                        if(getBlockStoreMatrixElement(i+1,j)> 0 ||
                                getBlockStoreMatrixElement(i+1,j) == -1)
                            return true;
                    }
                }
            }
        }
        else if(sd == RIGHT)
        {
            for(int i=0; i<MATRIX_ROWS; i++)
            {
                for(int j=0; j<MATRIX_COLS; j++)
                {
                    if(single_block[i][j] > 0)
                    {
                        if(getBlockStoreMatrixElement(i,j+1)> 0
                                || getBlockStoreMatrixElement(i,j+1) ==
                                -1)
                            return true;
                    }
                }
            }
        }
        else if(sd == LEFT)
        {
            for(int i=0; i<MATRIX_ROWS; i++)
            {
                for(int j=0; j<MATRIX_COLS; j++)
                {
                    if(single_block[i][j] > 0)
                    {
                        if(getBlockStoreMatrixElement(i,j-1)> 0 ||
                                getBlockStoreMatrixElement(i,j-1) == -1)
                            return true;
                    }
                }
            }
        }
        return false;
    }
    bool isBlockStoreFull()
    {
        for(int j=0; j<MATRIX_COLS; j++)
        {
//if the first row has blocks
            if(block_store[0][j] > 0)
                return true;
        }
        return false;
    }
    bool isCompleteRow(int row)
    {
        for(int j=0; j<MATRIX_COLS; j++)
        {
//if you find an empty spot return false
            if(block_store[row][j] == 0)
                return false;
        }
        pcResult+=4;
        return true;
    }
    void shiftBlocksDown()
    {
        for(int i=0; i<MATRIX_ROWS; i++)
        {
            if(isCompleteRow(i))
            {
//do the shift starting from the row
//which is full moving backwords to
//reach the top of the matrix
                for(int k=i; k>0; k--)
                {
//first clear the full row
                    for(int j=0; j<MATRIX_COLS; j++)
                    {
                        block_store[k][j]=0;
                    }
//second: move the data of the above row to
//the full row
                    for(j=0; j<MATRIX_COLS; j++)
                    {
                        block_store[k][j]=block_store[k-1][j];
                    }
                }
            }
        }
    }
    void DrawBlockStoreMatrix(void)
    {
        int unit=game_settings.getGameRectLength();
//this function to scan the blocks_store matrix and
// if find an element not zero, so it will draw a single
// rectangle "block element" in the corrisponding pos.
        int combined_element;
        for(int i=0; i<MATRIX_ROWS; i++)
            for(int j=0; j<MATRIX_COLS; j++)
            {
                combined_element=block_store[i][j]+single_block[i][j];
                if(combined_element!=0 )
                {
                    RECTANGLE
                    temp_rect= {6*unit+j*unit,unit+i*unit,6*unit+j*unit+unit,unit+i*unit+unit};
                    paint_background.DrawTexturedRectangle(temp_rect,combined_element+4);
                }
            }
    }
    void addBlockToBlockStore()
    {
        for(int i=0; i<MATRIX_ROWS; i++)
        {
            for(int j=0; j<MATRIX_COLS; j++)
                block_store[i][j]=block_store[i][j]+single_block[i][j];
        }
    }
    void UpdateSingleBlockMatrix(Block *current_block)
    {
//get the block info
        int row =current_block->getRow();
        int col =current_block->getCol();
        int rotation=current_block->getRotation();
        int shape_value=current_block->getShape();
//set all elements to be all zeroes
        ClearSingleBlockMatrix();
        switch(shape_value)
        {
        case 1: //T shape
            if(rotation == 1)
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col-1,shape_value);
                setSingleBlockElement(row-1,col+1,shape_value);
            }
            else if(rotation == 2)
            {
// this shape |-
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col+1,shape_value);
                setSingleBlockElement(row-2,col,shape_value);
            }
            else if(rotation == 3)
            {
// this shape _|_
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row,col+1,shape_value);
                setSingleBlockElement(row-1,col+1,shape_value);
                setSingleBlockElement(row,col+2,shape_value);
            }
            else
            {
// this shape -|
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col-1,shape_value);
                setSingleBlockElement(row-2,col,shape_value);
            }
            break;
        case 2: //L shape
            if(rotation == 1)
            {
//this shape |_
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row,col+1,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-2,col,shape_value);
            }
            else if(rotation == 2)
            {
// this shape ___|
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row,col+1,shape_value);
                setSingleBlockElement(row,col+2,shape_value);
                setSingleBlockElement(row-1,col+2,shape_value);
            }
            else if(rotation == 3)
            {
// this shape ''|
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-2,col,shape_value);
                setSingleBlockElement(row-2,col-1,shape_value);
            }
            else
            {
// this shape |'''''
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col+1,shape_value);
                setSingleBlockElement(row-1,col+2,shape_value);
            }
            break;
        case 3: //Z shape
            if(rotation == 1)
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row,col+1,shape_value);
                setSingleBlockElement(row-1,col+1,shape_value);
                setSingleBlockElement(row-1,col+2,shape_value);
            }
            else if(rotation == 2)
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col-1,shape_value);
                setSingleBlockElement(row-2,col-1,shape_value);
            }
            else if(rotation == 3)
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row,col+1,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col-1,shape_value);
            }
            else
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-1,col+1,shape_value);
                setSingleBlockElement(row-2,col+1,shape_value);
            }
            break;
        case 4: //I shape
            if((rotation % 2) == 0)
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row,col+1,shape_value);
                setSingleBlockElement(row,col+2,shape_value);
                setSingleBlockElement(row,col+3,shape_value);
            }
            else
            {
                setSingleBlockElement(row,col,shape_value);
                setSingleBlockElement(row-1,col,shape_value);
                setSingleBlockElement(row-2,col,shape_value);
                setSingleBlockElement(row-3,col,shape_value);
            }
            break;
        case 5: //O shape
            setSingleBlockElement(row,col,shape_value);
            setSingleBlockElement(row-1,col,shape_value);
            setSingleBlockElement(row,col+1,shape_value);
            setSingleBlockElement(row-1,col+1,shape_value);
            break;
        default:
            break;
        }
    }
}
static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void display()
{
    if(current_state.getState() == 2)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1,1,1);
        paint_background.DrawBackgroundImage();
        glColor3f(0,0,0);
        paint_background.DrawGameSubwindows();
//if there is a complete row shift down
        game_matrix.shiftBlocksDown();
        if(game_matrix.isBlockTouchBlock(BOTTOM))
        {
            if(game_matrix.isBlockStoreFull())
            {
//game over
                current_moving_block.haltGame();
                paint_background.printMessageGameOver();
                pcResult=0;
                game_settings.resetElapsedTime();
                game_matrix.ClearBlockStoreMatrix();
            }
            else
            {
//if block touches block save the current block
//to the block store and start new shape
                current_moving_block.resetBlock();
                game_matrix.addBlockToBlockStore();
            }
        }
        else
        {
            current_moving_block.MoveBottom(false);
        }
//apply changes of the block pos to the current
//block
        game_matrix.UpdateSingleBlockMatrix(&current_moving_block);
        glColor3f(1.0f,1.0f,1.0f);
        game_matrix.DrawBlockStoreMatrix();
        glColor3f(1.0f,1.0f,1.0f);
        if(current_moving_block.isHaltMode())
        {
            paint_background.printMessageEsc();
        }
    }
    else if(current_state.getState() == 1)
    {
//Menu screen
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1,1,1);
        paint_background.DrawBackgroundImage();
        glColor3f(0.6,0.3,0.6);
        paint_background.DrawGameMenu();
    }
    else if(current_state.getState() == 3)
    {
//top score screen
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
    }
    glutSwapBuffers();
}

void keyboard_s (int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if(current_state.getState() == 2)
        {
            current_moving_block.RotateShape();
        }
        else if(current_state.getState() == 1)
        {
            paint_background.setPrevMenuItem();
        }
        break;
    case GLUT_KEY_DOWN:
        if(current_state.getState() == 2)
        {
//move the block until it touches other block
            while( ! game_matrix.isBlockTouchBlock(BOTTOM) )
            {
                current_moving_block.MoveBottom(true);
                game_matrix.UpdateSingleBlockMatrix(&current_moving_block);
            }
            game_settings.increaseElapsedTime();
        }
        else if(current_state.getState() == 1)
        {
            paint_background.setNextMenuItem();
        }
        break;
    case GLUT_KEY_LEFT:
        if(! game_matrix.isBlockTouchBlock(LEFT))
        {
            current_moving_block.MoveLeft();
            game_matrix.UpdateSingleBlockMatrix(&current_moving_block);
        }
        break;
    case GLUT_KEY_RIGHT:
        if(! game_matrix.isBlockTouchBlock(RIGHT))
        {
            current_moving_block.MoveRight();
            game_matrix.UpdateSingleBlockMatrix(&current_moving_block);
        }
        break;
    }
}

static void idle(void)
{
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.7, 0.9, 1.0, 0.0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Tetris Game");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    //glutKeyboardFunc(key);
    //glutIdleFunc(idle);

    init();
    glutMainLoop();

    return EXIT_SUCCESS;
}
