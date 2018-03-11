package sorman;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;

/**
 * @author Serkan Sorman
 */

/**
 * This class plays ConnectFour game
 */
public class ConnectFour {
    
    /**
     * Includes information of every cells in board
     * 
     * */
     private class Cell{//
        
        /**Holds information of cells:Empty,User1,User2 as a  0,1,2 respectively*/
        private int type;
        
        Cell(){
            type = 0;
        }
        
        /**
         * Set the cell's type
         * @param token user1,user2 or empty as a 0,1,2
         */
        private void setType(int token){
            type = token;
        }
        
        /**
         * Access the cell's type
         * @return user1,user2 or empty as a 0,1,2
         */
        private int getType(){
            return type;
        } 
    }
     
    /**Frame of game*/
    private JFrame frame;
    /**Cells on board*/
    private JLabel[][] cells;
    /**Top buttons that provides making player moves*/
    private JButton[] buttons;
    /**Game board size*/
    private int size;
    /**Sequence of player*/
    private int player = 1;
    /**Indıcates computer first move*/
    private boolean isFirstMove = true;
    /**PvP or PvC*/
    private String gameMode;
    /**Game board matrix with Cell type*/
    private Cell [][]gameCells;
    
  
    /**Constructs all gui components and board*/
    public ConnectFour() {

        frame = new JFrame("Connect Four");
        JPanel panel = (JPanel) frame.getContentPane();
        /**Players choose PvP or PvC*/
        int op = option();
        inputSize();
        panel.setLayout(new GridLayout(size+1, size));
        initBoard();
        
        makeButtons(op,panel);
        makeBoard(panel);
        setFrame(panel);
      
    }
   
    /**
     * Creates top buttons,add them panels and handle with action
     * @param option PvP or PvC
     * @param panel  ConnectFour panel
     */
    private void makeButtons(int option,JPanel panel){
        
        buttons = new JButton[size];
        for (int i = 0; i < size; i++) {//Constructs Top buttons
            buttons[i] = new JButton();
            ImageIcon imageIcon = new ImageIcon("Images/arrow.png"); // 
            Image image = imageIcon.getImage(); // transform it 
            Image newimg = image.getScaledInstance(500/size,500/size,java.awt.Image.SCALE_SMOOTH); // scale image  
            imageIcon  = new ImageIcon(newimg);
            buttons[i].setIcon(imageIcon);
            buttons[i].setBackground(Color.ORANGE);
            buttons[i].setActionCommand("" + i);
            buttons[i].addActionListener(new ActionListener() {
                
                @Override
                public void actionPerformed(ActionEvent e)
                {
                    int colNum = Integer.parseInt(e.getActionCommand());
                    if(option == 0)
                        playPvP(colNum);
                    else
                        playPvC(colNum);  
                }  
            });  
            panel.add(buttons[i]);
        }
    }
    
    /**
     * Creates empty cells on board 
     * @param panel ConnectFour panel
     */
    private void makeBoard(JPanel panel){
        
        cells = new JLabel[size][size];
        for (int row = 0; row < size; row++) {
            for (int column = 0; column < size; column++) {
                ImageIcon imageIcon = new ImageIcon("Images/empty.png"); 
                Image image = imageIcon.getImage(); 
                Image newimg = image.getScaledInstance(500/size,500/size,java.awt.Image.SCALE_SMOOTH); // scale image  
                imageIcon  = new ImageIcon(newimg);  
                cells[row][column] = new JLabel();
                cells[row][column].setIcon(imageIcon);
                cells[row][column].setHorizontalAlignment(SwingConstants.CENTER);
                cells[row][column].setBorder(new LineBorder(Color.black));
                panel.add(cells[row][column]);
            }
        }
    }
    
    /**
     * Set frame properties
     * @param panel ConnectFour panel
     */
    void setFrame(JPanel panel){
        
        frame.setSize(800,700);
        frame.setContentPane(panel);
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setBackground(Color.ORANGE);
    }
    
    /**Takes board size from user and checks it isLegal*/
    private void inputSize(){
        String sizeStr = JOptionPane.showInputDialog("Please enter size of board");
        if(sizeStr == null){//if user clicks cancel
            frame.dispose();
            System.exit(0);
        }
        
        while(sizeStr.isEmpty() || sizeStr.matches("[A-Za-z]*") || sizeStr.equals(" ")){//Takes input until size is legal
            sizeStr = JOptionPane.showInputDialog("Invalid size !!! Try again");
            if(sizeStr == null){
                frame.dispose();
                System.exit(0);
            }
        }
        
        int tempSize = Integer.parseInt(sizeStr);
        while(!isLegalSize(tempSize)){//Takes input until size is legal
            sizeStr = JOptionPane.showInputDialog("Invalid size !!! Try again");
            if(sizeStr == null){
                frame.dispose();
                System.exit(0);
            }
            tempSize = Integer.parseInt(sizeStr);
        }
        size = tempSize;
            
    }  
    
    /**
     * Checks whether the user's input size is legal
     * @param size Board size
     * @return size Legal or not
     */
    private boolean isLegalSize(int size){
	return size >= 4;
    }
    
    /**
     * Checks coordinates to prevent reach out of board
     * @param coordX x position
     * @param coordY y position
     * @return Coordinate is legal or not
     */
    private boolean isLegalPos(int coordX,int coordY){
	return coordX >=0 && coordX < size && coordY >= 0 && coordY<size;
    }
    
    /**
     * Checks whether the selected column is full
     * @param colNum Column that player moved
     * @return Full or not
     */
    private boolean isColumnFull(int colNum){
	int counter = 0;
        
	for(int i=0;i<size;++i)
            if(gameCells[i][colNum].getType() != 0)
                counter++;
        
	return counter == size;
    }
    
    /**
     * Checks board is full or not
     * @return Full or not
     */
    private boolean isBoardFull(){
	int counter = 0;
       
	for(int i=0;i<size;++i)
            for(int j=0;j<size;++j)
                if(gameCells[i][j].getType() != 0)
                    counter++;
        
	return counter == size*size;
    }
    
    /**
     * Creates a board matrix
     * 
     */
    private  void initBoard(){
      
      gameCells =  new Cell[size][size];
      for(int i=0;i<size;i++){
        gameCells[i] = new Cell[size];
        for(int j=0;j<size;j++)
            gameCells[i][j] = new Cell();  
      }
          
    }
    
    
    /**
     * Sets image to cell
     * @param imageName Cell's image
     * @param row position of cell
     * @param column position of cell
     */
    private void setImage(String imageName,int row,int column){
        
        ImageIcon imageIcon = new ImageIcon(imageName); // load the image to a imageIcon
        Image image = imageIcon.getImage(); // transform it 
        Image newimg = image.getScaledInstance(700/size,600/size,java.awt.Image.SCALE_SMOOTH); // scale it the smooth way  
        imageIcon  = new ImageIcon(newimg);  // transform it back*/
        cells[row][column].setIcon(imageIcon);
    }
    
    /**Updates board on screen after users are played*/
    private void updateBoard() {
        for (int row = 0; row < size; row++) {
            for (int column = 0; column < size; column++) {   
                if (gameCells[row][column].getType() == 1) //Put red disc to cell
                    setImage("Images/user1.png",row,column);
                if (gameCells[row][column].getType() == 2) //Put black disc to cell
                    setImage("Images/user2.png",row,column);
                
            }
        }
    }
    
    /**
     * Makes moves of user1 or user2 
     * @param colNum Column that player moved
     */
    private void playerMove(int colNum) {
        
        for(int i=size - 1;i>=0;--i){
            for(int j=size - 1;j>=0;--j){
                if(j == colNum && gameCells[i][j].getType() == 0 ){// Puts red  Or black disc according to current player
                    if(player % 2 == 1 || gameMode.equals("PvC") ){
                        gameCells[i][j].setType(1);
                        return;
                    }
                    else if(player % 2 == 0 && gameMode.equals("PvP")){
                        gameCells[i][j].setType(2);
                        return;
                    }
                }
                
            }
	}
    }
    
    /**Makes computer's move*/
    private void computerMove(){
        
        if(isThreeVertical() || isThree()); //First priority attack
        else if(defend3Vertical() || Defend3());//Second priority defence
	else if(isTwoVertical()  || isTwo());
        else if(isOneVertical() || isOne());
	else
            defaultOne();
	
	player = 2;//Computer is player 2
	
    }
    
    /**
     * Checks whether the four same cells are neighbor horizontally
     * @return if finds same four neighbor cells, returns true
     */
    private boolean checkHorizon()
    {
	int count = 0;

	for(int i=size - 1;i>=0;--i){
            for(int j=0;j<size;++j){
                if((gameCells[i][j].getType() == 1 && player % 2 == 1) || 
                   (gameCells[i][j].getType() == 2 && player % 2 ==  0))
                    ++count; // Counts same cells horizontally
                else
                    count = 0;
                if(count == 4){	// if there are four same neighbor cells
                    for(int a=0;a<4;a++){ // Converts them star disc
                        if(player % 2 == 1)
                            setImage("Images/user1Win.png",i,j-a);
                        else
                            setImage("Images/user2Win.png",i,j-a);
                    }
                    return true;
                }		
            }
            count = 0;
        }
        return false;
    }


    /**
     * Checks whether the four same cells are neighbor vertically 
     * @return if finds same four neighbor cells, returns true
     */
    private boolean checkVertical()
    {
        int count = 0;

        for(int i=size - 1;i>=0;--i){
            for(int j=size-1;j>=0;--j){
                if(isLegalPos(j,i)){
                    if((gameCells[j][i].getType() == 1 && player % 2 == 1) || 
                       (gameCells[j][i].getType() == 2 && player % 2 == 0))
                       ++count; // Counts same cells vertically
                    else
                        count = 0;
                    if(count == 4){ // if there are four same neighbor cells
                        for(int a=0;a<4;a++){ // Converts them star disc
                                if(player % 2 == 1)
                                setImage("Images/user1Win.png",j+a,i);
                            else
                                setImage("Images/user2Win.png",j+a,i);
                        }
                        return true;
                    }
                }		
            }
                count = 0;
        }
        return false;
    }
    
    /**
     * Checks whether the four same cells are neighbor in right cross
     * @return if finds same four neighbor cells, returns true
     */
    private boolean checkDiaRight()
    {
        for(int i=size - 1;i>=0;--i){
            for(int j=0;j<size;++j){
                if(isLegalPos(i-1,j+1) && isLegalPos(i-2,j+2) && isLegalPos(i-3,j+3)){
                    if( (gameCells[i][j].getType() == 1 && gameCells[i-1][j+1].getType() == 1//Four same neighbor player 1
                        && gameCells[i-2][j+2].getType() == 1 && gameCells[i-3][j+3].getType() == 1) ||

                       (gameCells[i][j].getType() == 2 && gameCells[i-1][j+1].getType() == 2//Four same neighbor player 2
                        && gameCells[i-2][j+2].getType() == 2 && gameCells[i-3][j+3].getType() == 2)){	
                       for(int a=0;a<4;a++){ // Converts them star disc
                            if(player % 2 == 1)
                                setImage("Images/user1Win.png",i-a,j+a);
                            else
                                setImage("Images/user2Win.png",i-a,j+a);
                        }
                       return true;
                    }
                }
            }
        }
        return false;			
    }

    /**
     * Checks whether the four same cells are neighbor in left cross
     * @return if finds same four neighbor cells, returns true
     */
    private boolean checkDiaLeft()
    {
        for(int i=size - 1;i>=0;--i){
            for(int j=0;j<size;++j){
                if(isLegalPos(i-1,j-1) && isLegalPos(i-2,j-2) && isLegalPos(i-3,j-3)){
                    if( (gameCells[i][j].getType() == 1 && gameCells[i-1][j-1].getType() == 1//Four same neighbor player 1
                    && gameCells[i-2][j-2].getType() == 1 && gameCells[i-3][j-3].getType() == 1) ||

                   (gameCells[i][j].getType() == 2 && gameCells[i-1][j-1].getType() == 2//Four same neighbor player 2
                    && gameCells[i-2][j-2].getType() == 2 && gameCells[i-3][j-3].getType() == 2)){	
                        for(int a=0;a<4;a++){ // Converts them star disc
                                if(player % 2 == 1)
                                setImage("Images/user1Win.png",i-a,j-a);
                            else
                                setImage("Images/user2Win.png",i-a,j-a);
                        }
                        return true;
                    }
                }
            }
        }
        return false;	
    }
    
    /**
     * Checks All position for end of the game
     * @return if any position is exist return true
     */
    private boolean checkAll(){
        return checkHorizon() || checkVertical() || 
               checkDiaLeft() || checkDiaRight();
    }
    

    /**
     * Adds a neighbor cell to a single cell of the computer
     * @return true if finds convenient position
     */
    private boolean isOneVertical(){
        for(int i=0;i<size;++i){
            for(int j=size-1;j>=0;--j){
                if(isLegalPos(j-1,i) && isLegalPos(j,i)){
                    if(gameCells[j][i].getType() == 2 && gameCells[j-1][i].getType() == 0){
                        //Checks whether there is a single cell and adds cell vertically
                        gameCells[j-1][i].setType(2);
                        return true;
                    }
                }
            }
        }	
        return false;
    }
    
    /**
     * Adds a neighbor cell to two cells of the computer vertically
     * @return true if finds convenient position
     */
    private boolean isTwoVertical(){
        for(int i=0;i<size;++i){
            for(int j=size-1;j>=0;--j){
                if(isLegalPos(j-2,i) && isLegalPos(j,i)){
                    if(gameCells[j][i].getType() == 2 && gameCells[j-1][i].getType() == 2 && gameCells[j-2][i].getType() == 0 ){
                    //Checks whether there are two neigbor cells and adds cell vertically
                    gameCells[j-2][i].setType(2);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * Adds a neighbor cell to three cells of the computer vertically
     * @return true if finds convenient position
     */
    private boolean isThreeVertical(){
        for(int i=0;i<size;++i){
            for(int j=size-1;j>=0;--j){
                if(isLegalPos(j-3,i) && isLegalPos(j,i)){
                    if(gameCells[j][i].getType() == 2 && gameCells[j-1][i].getType() == 2  && gameCells[j-2][i].getType() == 2 && gameCells[j-3][i].getType() == 0 ){
                            //Checks whether there are three neigbor cell and adds cell vertically
                            gameCells[j-3][i].setType(2);
                    return true;
                        }
                }
            }
        }
        return false;
    }
    
    /**
     * Blocks opponents three neighbor cells vertically
     * @return true if finds convenient position
     */
    private boolean defend3Vertical(){
        for(int i=0;i<size;++i){
            for(int j=size-1;j>=0;--j){
                if(isLegalPos(j-3,i) && isLegalPos(j,i)){
                    if(gameCells[j][i].getType() == 1 && gameCells[j-1][i].getType() == 1  && gameCells[j-2][i].getType() == 1 && gameCells[j-3][i].getType() == 0 ){
                            //Checks whether there are three neighbor opponent's cell and adds 1 vertically
                            gameCells[j-3][i].setType(2);
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    /**
     * Moves any empty cells
     * @return true if finds convenient position
     */
    private boolean defaultOne()
    {
            for(int i=size - 1;i>=0;--i){ // if there arent any neighbor,moves empty column
                for(int j=0;j<size;++j){
                    if(gameCells[i][j].getType() == 0){
                        gameCells[i][j].setType(2);
                        return true;
                    }
                }
            }
            return false;
    }
    
    /**
     * Adds a neighbor cell to a single cell of the computer
     * @return true if finds convenient position
     */
    private boolean isOne()
    {
        for(int i=size - 1;i>=0;--i){
            for(int j=0;j<size;++j){
                if(isLegalPos(i,j+1) && isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 0
                     &&  i == size -1){
                        //Checks whether there is a single cell and adds cell in horizontal right side
                        gameCells[i][j+1].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i+1,j+1) && isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 0 &&  
                            gameCells[i+1][j+1].getType() != 0){
                            //Checks whether there is a single cell and adds cell in horizontal right side
                            gameCells[i][j+1].setType(2);
                            return true;
                    }
                }
                if(isLegalPos(i,j+1)&& isLegalPos(i,j) && isLegalPos(i,j-1)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() != 0 &&
                         gameCells[i][j-1].getType() == 0 && 
                                i == size - 1 ){
                                //Checks whether there is a single cell and adds cell in horizontal left side
                                gameCells[i][j-1].setType(2);
                                return true;
                        }
                }
                if(isLegalPos(i+1,j+1)&& isLegalPos(i,j) && isLegalPos(i,j-1)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() != 0 
                                && gameCells[i][j-1].getType() == 0 && 
                                 gameCells[i+1][j-1].getType() != 0){
                                //Checks whether there is a single cell and adds cell in horizontal left side
                                gameCells[i][j-1].setType(2);
                                return true;
                        }
                }
                if(isLegalPos(i-1,j+1)&& isLegalPos(i,j)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i-1][j+1].getType() == 0 &&
                         gameCells[i][j+1].getType() != 0 && isLegalPos(i-1,j+1)){
                                gameCells[i-1][j+1].setType(2);
                                //Checks whether there is a single cell and adds cell in right cross side
                                return true;
                        }
                }
                if(isLegalPos(i-1,j-1)&& isLegalPos(i,j)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i-1][j-1].getType() == 0 && 
                                gameCells[i][j-1].getType() != 0 && isLegalPos(i-1,j-1)){
                                //Checks whether there is a single cell and adds cell in left cross side
                                gameCells[i-1][j-1].setType(2);
                                return true;
                        }
                }
            }	
        }
        return false;
    }
    
    /**
     * Adds a neighbor cell to two cells of the computer
     * @return true if finds convenient position
     */
    private boolean isTwo()
    {
        for(int i=size - 1;i>=0;--i){
            for(int j=0;j<size;++j){
                if(isLegalPos(i,j+2) && isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 &&
                     gameCells[i][j+2].getType() == 0 && i == size -1 ){
                            //Checks whether there are two neighbor cells and adds cell in horizontal right side
                            gameCells[i][j+2].setType(2);
                            return true;
                    }
                }
                if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 &&
                         gameCells[i][j+2].getType() == 0 && gameCells[i+1][j+2].getType() != 0){
                                //Checks whether there are two neighbor cells and adds cell in horizontal right side
                                gameCells[i][j+2].setType(2);
                                return true;
                        }
                }
                if(isLegalPos(i,j+2) && isLegalPos(i,j) && isLegalPos(i,j-1)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 && 
                        gameCells[i][j+2].getType() != 0 && gameCells[i][j-1].getType() == 0 && 
                        i == size - 1 ){
                        //Checks whether there are two neighbor cells and adds cell in horizontal left side
                        gameCells[i][j-1].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i+1,j+2) && isLegalPos(i,j) && isLegalPos(i,j-1)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 && 
                        gameCells[i][j+2].getType() != 0 && gameCells[i][j-1].getType() == 0 && 
                         gameCells[i+1][j-1].getType() != 0){
                        //Checks whether there are two neighbor cells and adds cell in horizontal left side
                        gameCells[i][j-1].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i-1][j+1].getType() == 2 && 
                        gameCells[i-2][j+2].getType() == 0 && gameCells[i-1][j+2].getType() != 0 ){
                        gameCells[i-2][j+2].setType(2);
                        //Checks whether there are two neighbor cells and adds cell in right cross side
                        return true;
                    }
                }
                if(isLegalPos(i-2,j-2) && isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 2 && gameCells[i-1][j-1].getType() == 2 && 
                            gameCells[i-2][j-2].getType() == 0 && gameCells[i-1][j-2].getType() != 0){
                            //Checks whether there are two neighbor cells and adds cell in left cross side
                            gameCells[i-2][j-2].setType(2);
                            return true;
                    }
                }
            }	
        }
        return false;
    }
    
     /**
     * Adds a neighbor cell to three cells of the computer
     * @return true if finds convenient position
     */
    private boolean isThree()
    {
        if(isFirstMove){//Computer first move
                isFirstMove = false;
                if(gameCells[size - 1][size/2].getType()== 0)
                        gameCells[size - 1][size/2].setType(2);
                else
                    gameCells[size - 1][(size/2)-1].setType(2);
                return true;
        }
        else{
            for(int i=size - 1;i>=0;--i){
               for(int j=0;j<size;++j){
                   if(isLegalPos(i,j+3) && isLegalPos(i,j)){
                       if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 && 
                            gameCells[i][j+2].getType() == 2 && gameCells[i][j+3].getType() == 0 && i == size -1 ){
                            //Checks whether there are three neighbor cells and adds cell in horizontal right side
                            gameCells[i][j+3].setType(2);
                            return true;
                       }
                   }
                   if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 &&
                         gameCells[i][j+2].getType() == 2 && gameCells[i][j+3].getType() == 0 && gameCells[i+1][j+3].getType() != 0){
                                //Checks whether there are three neighbor cells and adds cell in horizontal right side
                                gameCells[i][j+3].setType(2);
                                return true;
                        }
                    }    
                    if(isLegalPos(i,j+3) && isLegalPos(i,j) && isLegalPos(i,j-1)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 && 
                            gameCells[i][j+2].getType() == 2&& gameCells[i][j+3].getType() != 0 && gameCells[i][j-1].getType() == 0 && 
                            i == size - 1 ){
                            //Checks whether there are three neighbor cells and adds cell in horizontal left side
                            gameCells[i][j-1].setType(2);
                            return true;
                        }
                    }
                    if(isLegalPos(i+1,j+3) && isLegalPos(i,j) && isLegalPos(i,j-1)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i][j+1].getType() == 2 && gameCells[i][j+2].getType() == 2 &&
                            gameCells[i][j+3].getType() != 0 && gameCells[i][j-1].getType() == 0 && 
                             gameCells[i+1][j-1].getType() != 0){
                            //Checks whether there are three neighbor cells and adds cell in horizontal left side
                            gameCells[i][j-1].setType(2);
                            return true;
                        }
                    }
                    if(isLegalPos(i-3,j+3) && isLegalPos(i,j)){
                        if(gameCells[i][j].getType() == 2 && gameCells[i-1][j+1].getType()== 2 && gameCells[i-2][j+2].getType()== 2 && 
                            gameCells[i-3][j+3].getType()== 0 && gameCells[i-2][j+3].getType()!= 0 && isLegalPos(i-3,j+3)){
                            //Checks whether there are three neighbor cells and adds cell in right cross side
                            gameCells[i-3][j+3].setType(2);
                            return true;
                        }
                    }
                    if(isLegalPos(i-3,j-3) && isLegalPos(i,j)){
                            if(gameCells[i][j].getType() == 2 && gameCells[i-1][j-1].getType()== 2 && gameCells[i-2][j-2].getType()== 2 && 
                                gameCells[i-3][j-3].getType()== 0 && gameCells[i-2][j-3].getType()!= 0 && isLegalPos(i-3,j-3)){
                                //Checks whether there are three neighbor cells and adds cell in left cross side
                                gameCells[i-3][j-3].setType(2);
                                return true;
                            }
                    }
                }	
            }
        return false;
        }
    }
    
     /**
     * Blocks opponents three neighbor cells
     * @return true if finds convenient position
     */
    private boolean Defend3()
    {	
        //Like isThree function,checks whether there are three opponent's neighbor cells and adds computer's cell around cell
         for(int i=size - 1;i>=0;--i){
            for(int j=0;j<size;++j){
                if(isLegalPos(i,j+3)&& isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 1 && gameCells[i][j+1].getType() == 1 && 
                        gameCells[i][j+2].getType() == 1 && gameCells[i][j+3].getType() == 0 && i == size -1 ){
                        //Checks whether there is a single cell and adds cell in horizontal right side
                        gameCells[i][j+3].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 1 && gameCells[i][j+1].getType() == 1 && gameCells[i][j+2].getType() == 1
                        && gameCells[i][j+3].getType() == 0 && gameCells[i+1][j+3].getType() != 0){
                        //Checks whether there is a single cell and adds cell in horizontal right side
                        gameCells[i][j+3].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i,j+3)&& isLegalPos(i,j) && isLegalPos(i,j-1)){
                    if(gameCells[i][j].getType() == 1 && gameCells[i][j+1].getType() == 1 && gameCells[i][j+2].getType() == 1
                        && gameCells[i][j+3].getType() != 0 && gameCells[i][j-1].getType() == 0 && i == size - 1 ){
                        //Checks whether there is a single cell and adds cell in horizontal left side
                        gameCells[i][j-1].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i+1,j+3)&& isLegalPos(i,j) && isLegalPos(i,j-1)){
                    if(gameCells[i][j].getType() == 1 && gameCells[i][j+1].getType() == 1 && gameCells[i][j+2].getType() == 1
                        &&gameCells[i][j+3].getType() != 0 && gameCells[i][j-1].getType() == 0 && gameCells[i+1][j-1].getType() != 0){
                        //Checks whether there is a single cell and adds cell in horizontal left side
                        gameCells[i][j-1].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i-3,j+3)&& isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 1 && gameCells[i-1][j+1].getType()== 1 && gameCells[i-2][j+2].getType()== 1
                        && gameCells[i-3][j+3].getType()== 0 && gameCells[i-2][j+3].getType()!= 0 && isLegalPos(i-3,j+3)){
                        //Checks whether there are three neighbor cells and adds cell in right cross side
                        gameCells[i-3][j+3].setType(2);
                        return true;
                    }
                }
                if(isLegalPos(i-3,j-3)&& isLegalPos(i,j)){
                    if(gameCells[i][j].getType() == 1 && gameCells[i-1][j-1].getType()== 1 && gameCells[i-2][j-2].getType()== 1
                        && gameCells[i-3][j-3].getType()== 0 && gameCells[i-2][j-3].getType()!= 0 && isLegalPos(i-3,j-3)){
                        //Checks whether there are three neighbor cells and adds cell in left cross side
                        gameCells[i-3][j-3].setType(2);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * Checks end of the game is draw or win and asks for a new game
     */
    private void endGame() {
          String endMessage = "THE GAME END İN DRAW";
        //if game ended with no one win,it means draw
        if(checkAll()){
            if(player % 2 == 1)
                endMessage = "PLAYER 1 WİN !!!";
            else if(player % 2 == 0 && gameMode.equals("PvP"))
                endMessage = "PLAYER 2 WİN !!!";
            else if(player % 2 == 0 && gameMode.equals("PvC")){
                endMessage = "YOU LOSE !!!";
            }
        }
        //After game end,asks play again
        int result = JOptionPane.showConfirmDialog(frame,"Do you want new game ?",endMessage,JOptionPane.YES_NO_OPTION);
        if (result < 1) {
            frame.dispose();
            initBoard();
            ConnectFour game = new ConnectFour();//Create a new game
        } else{
            initBoard();
            frame.dispose();//Completely exit game
        }
    }
    
    /**
     * Plays game in PvP mode
     * @param colNum Column that user's played
     */
    private void playPvP(int colNum){
        gameMode = "PvP";
        if(isColumnFull(colNum))
            JOptionPane.showMessageDialog(null, "Choose another column.", "Column is full.", JOptionPane.INFORMATION_MESSAGE);
        else{
            int sequence;
            if(player % 2 == 1)//Set the sequence to  shown on top left corner
                sequence = 2;
            else
                sequence = 1;
            frame.setTitle("Connect Four - Player " +  sequence + "'s turn");
            playerMove(colNum);
            updateBoard();
            if(checkAll()) //Checks after users played             
                endGame();
            ++player;   //Changes the player
        }
     
        if(isBoardFull())
          endGame();  
    }
    
    /**
     * Plays game in PvC mode
     * @param colNum Column that user's played
     */
    private void playPvC(int colNum){

        gameMode = "PvC";
        if(isColumnFull(colNum))
            JOptionPane.showMessageDialog(null, "Choose another column.", "Column is full.", JOptionPane.INFORMATION_MESSAGE);
        else{
            playerMove(colNum);
            player = 1;
            updateBoard();
            if(checkAll())//Checks after user played
                endGame();
            computerMove();
            updateBoard();
            if(checkAll())//Checks after computer played
                endGame();
            
        }
        if(isBoardFull())
            endGame();
    }
    
    /**
     * Show option dialog for game mode
     * @return index of chosen mode
     */
    private int option(){
         
        String[] options = {"Player vs Player","Player vs Computer"};
        int n = JOptionPane.showOptionDialog(null, "How do you want to play ?",
                "Game Mode",
                JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options, options[0]);
        
        return n;
    }
    
    public static void main(String[] args) {
        ConnectFour game = new ConnectFour();
       
    }
}


