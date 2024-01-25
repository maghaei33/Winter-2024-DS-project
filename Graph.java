
import java.awt.Color;

import javax.swing.JFrame;

public class Graph {

    public static void main(String[] args) throws Exception 
    {
        // Setting Frame class static variables
        Frame.rectWidth = 120;
        Frame.rectHeight = 40;
        Frame.RectColor = Color.LIGHT_GRAY;
        Frame.TextColor = Color.BLACK;
        Frame.LineColor = Color.DARK_GRAY;
        
        Frame frame = new Frame();
        frame.color = Color.red;

        frame.SetData(args);

        JFrame app = new JFrame();

        app.setTitle("Family Tree");
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        app.add(frame);
        app.setSize(640, 640);
        app.setVisible(true);
    }
}
