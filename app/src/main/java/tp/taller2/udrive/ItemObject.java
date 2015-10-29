package tp.taller2.udrive;

/**
 * Created by mati on 08/10/15.
 */
public class ItemObject {
    private String title;
    private int icon;

    public ItemObject(String title, int icon){
        this.title = title;
        this.icon = icon;
    }

    public String getTitle(){
        return title;
    }

    public void setTitle(String title){
        this.title = title;
    }

    public int getIcon(){
        return icon;
    }

    public void setIcon(int icon){
        this.icon = icon;
    }
}
