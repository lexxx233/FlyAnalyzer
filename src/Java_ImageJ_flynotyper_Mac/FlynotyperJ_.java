import ij.*;
import ij.process.*;
import ij.gui.*;
import ij.plugin.*;
import ij.plugin.frame.PlugInFrame;

/**
 *
 * @author qingyuwang
 */
public class FlynotyperJ_ extends PlugInFrame {
    	public FlynotyperJ_() {
		super("Flynotyper_");
		IJ.register(FlynotyperJ_.class);

        EyeGUI egui = new EyeGUI();
        egui.show();
    }
}
