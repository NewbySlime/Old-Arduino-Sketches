package ArduinoSketches.Sketches.References;

public class MakeBits {
    public static void main(String[] args) {
        functionMake8Bit();
    }

    static void functionMake8Bit(){
        /*
            var:
            int nBitArray;

            Do:
            -Give 1 from start
            -Move 1
            -the bit array stored in nBitArray convert it to string
            -then put the nres to theBits8
            -do it until bit in n 256

            Conditions:
            -if the front is 0, then move 1 one step
            -if the front is 1, then move 1 in the front one step, then remove 1s before it
            */
        
        char[] nBitArray = {'0','0','0','0','0','0','0','0'};

        for(int i = 1; i < 256; i++){ //iteration until 256
            boolean many = false;
            for(int o = 0; o < nBitArray.length; o++){
                if(nBitArray[7-o] == '1'){
                    many = true;
                    continue;
                }else{
                    nBitArray[7-o] = '1';
                    if(many){//happens when there's 1 infront of the original pos?
                        for(int z = o; z > 0; z--){//this is for removing the behind
                            nBitArray[8-z] = '0';
                        }
                    }
                    break;
                }
            }
            System.console().printf(new String(nBitArray) + " " + i + "\n");
        }
    }
}
