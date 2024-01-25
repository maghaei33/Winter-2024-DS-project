import java.awt.*;
import javax.swing.*;
import java.util.Hashtable;
import java.util.ArrayList;
import java.util.Enumeration;

public class Frame extends JPanel
{
    
    String RemoveCharsTill(String input, int index)
    {
        String Result = "";
        for (int i = index; i < input.length(); i++)
            Result += input.charAt(i);
        return Result;
    }

    /*  All x & y variables are center
        position of the rectangle    */

    public int size;
    public Color color;
    
    // Rect Properties
    static public int rectWidth;
    static public int rectHeight;
    
    // Colors 
    static public Color RectColor;
    static public Color TextColor;
    static public Color LineColor;

    private char layerSign = '$';
    private char childSign = '#';
    
    public int length;
    public int width[];

    ArrayList Tree = new ArrayList<Hashtable<String, Integer>>();

    void SetData(String[] data)
    {
        int currentRow = -1;
        length = Integer.parseInt(data[0]);
        int NotationStartIndex = length + 1;
        
        // Setting Width Array
        width = new int[length];
        for (int i = 1; i < NotationStartIndex; i++)
            width[i - 1] = Integer.parseInt(data[i]);

        String currentName = "";
        
        for (int i = NotationStartIndex; i < data.length; i++)
        {
            if (data[i].charAt(0) == layerSign)
            {
                currentRow++;
                Tree.add(new Hashtable<String, Integer>());
                continue;
            }
            else if (data[i].charAt(0) == childSign)
            {
                Hashtable<String, Integer> tempRow = (Hashtable<String, Integer>) Tree.get(currentRow);
                tempRow.replace(currentName, Integer.parseInt(RemoveCharsTill(data[i], 1)));
                Tree.set(currentRow, tempRow);
            }
            else 
            {
                Hashtable<String, Integer> tempRow = (Hashtable<String, Integer>) Tree.get(currentRow);
                currentName = data[i];
                tempRow.put(currentName, 0);
                Tree.set(currentRow, tempRow);
            }
        }
    }

    public boolean setWidthList(int[] width_list)
    {
        if (width_list.length != length) return false;

        for (int i = 0; i < this.length; i++)
        {
            this.width[i] = width_list[i];
        }

        return true;
    }

    static public int Height = 1;

    // returns top connect point of rect
    public static int[] getRectTop(int x, int y) { return new int[]{ x, y - rectHeight/2 }; }
    // returns bottom connect point of rect
    public static int[] getRectBottom(int x, int y) { return new int[]{ x, y + rectHeight/2 }; }

    // draw Function (works wtih center position)
    private void drawNameRect(Graphics graphic, String name, int x, int y)
    {
        drawRectInPosition(graphic, x, y);
        graphic.setColor(TextColor);
        graphic.drawChars(name.toCharArray(), 0, name.length(), x - rectWidth/2 + 5, y);
    }

    private void drawRectInPosition(Graphics graphic, int x, int y)
    {
        graphic.setColor(RectColor);
        graphic.fillRoundRect(
            x - rectWidth/2, 
            y - rectHeight/2, 
            rectWidth, 
            rectHeight, 
            10,
            10);
    }

    private void connectRects(Graphics graphic, int[] pos1, int[] pos2)
    {
        for (int i = -1; i < 2; i++)
            for (int j = -1; j < 2; j++)
                graphic.drawLine(pos1[0] + i, pos1[1] + rectHeight/2, pos2[0] + j, pos2[1] - rectHeight/2);
    }

    private void drawNameRectInLayout(Graphics graphic, String name, int layerIndex, int inRowIndex)
    {
        drawNameRect(
            graphic, 
            name, 
            getPositionInLayout(layerIndex, inRowIndex)[0], 
            getPositionInLayout(layerIndex, inRowIndex)[1]);
    }

    private int[] getPositionInLayout(int layerIndex, int inRowIndex)
    {
        return new int[]{ getWidth()/(this.width[layerIndex] + 1)*(1 + inRowIndex), getHeight()/(this.length + 1)*(1 + layerIndex) };
    }

    private void connectRectInLayout(Graphics graphic, int layerIndex1, int inRowIndex1, int layerIndex2, int inRowIndex2)
    {
        connectRects(graphic, getPositionInLayout(layerIndex1, inRowIndex1), getPositionInLayout(layerIndex2, inRowIndex2));
    }

    @Override
    public void paintComponent(Graphics graphic)
    {
        super.paintComponent(graphic);
        // Setting Font Style : Bold
        graphic.setFont(graphic.getFont().deriveFont((float) 13).deriveFont(1));
        graphic.setColor(color);  

        // Iteration References
        Hashtable<String, Integer> PrevTable = null;
        Hashtable<String, Integer> CurrentTable = (Hashtable<String, Integer>) Tree.get(0);
        int currentRowWidth = width[0];
        String currentName = CurrentTable.keys().nextElement();
        int[] childPartition = new int[] { CurrentTable.get(currentName) };

        // Draw First Rect
        drawNameRectInLayout(graphic, currentName, 0, 0);

        // Iterating Layers
        for (int currentLayerIndex = 1; currentLayerIndex < length; currentLayerIndex++)
        {
            PrevTable = CurrentTable;
            CurrentTable = (Hashtable<String, Integer>) Tree.get(currentLayerIndex);
            currentRowWidth = width[currentLayerIndex];

            // Saving this Row Child Partitions
            int[] tempChildPartitions = new int[currentRowWidth];
            
            // Draw Current Row Rects 
            Enumeration<String> names = CurrentTable.keys();
            // Iterating Rows 
            for (int indexInRow = 0; indexInRow < currentRowWidth; indexInRow++)
            {
                currentName = names.nextElement(); // Setting Current Name

                // Setting Child Partition
                tempChildPartitions[indexInRow] = CurrentTable.get(currentName); 
                
                // Drawing Rect
                drawNameRectInLayout(graphic, currentName, currentLayerIndex, indexInRow);
            }

            Enumeration<String> prevNames = PrevTable.keys();
            int currentChildPoint = 0;

            // Connect to Childs
            for (int prevInRowIndex = 0; prevInRowIndex < width[currentLayerIndex - 1]; prevInRowIndex++)
            {
                int currentChildCount = PrevTable.get(prevNames.nextElement());
                while (currentChildCount > 0)
                {
                    connectRectInLayout(graphic, currentLayerIndex - 1, prevInRowIndex, currentLayerIndex, currentChildPoint);
                    currentChildCount--;
                    currentChildPoint++;
                }
            }
        }
    }
}
