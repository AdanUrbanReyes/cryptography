import javax.swing.JFrame;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JButton;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
public class CheckBox extends JFrame implements ActionListener{
	private JCheckBox male,female;
	private JButton enter;
	private JPanel panel;
	public CheckBox(){
		super("CheckBox");
		setSize(400,400);
		setLayout(new GridLayout(1,1));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		panel=new JPanel(new GridLayout(0,1));
		add(panel);		
		
		String []sexo=new String{"male","female"};


		male=new JCheckBox("male");
		female=new JCheckBox("female");
		enter=new JButton("enter");
		enter.addActionListener(this);
		add(male);
		add(female);
		add(enter);
		setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e){
		if(male.isSelected()){
			System.out.print("male selected");
		}
		if(female.isSelected()){
			System.out.print("male selected");
		}
	}
	public static void main(String []args){
		CheckBox c=new CheckBox();
	}
}
1724