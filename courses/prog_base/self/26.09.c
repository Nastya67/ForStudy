int main(){
    int h = 0, m = 0;
    int code = 0;
    float price = 0;
    scanf ("%i, %i, %i", &h, &m, &code);
    switch (code) {
    case 44:
        price = 0.44*m + 60*h*0.44; break;
    case 666:
        price = 0; break;
    case 1:
        price = 30*m + 30*60*h; break;
       default:
        price = m + 60*h;

    }
printf ("%f", price); return 0;
}
