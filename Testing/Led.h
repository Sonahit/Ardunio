class Led {
    private:
        int pin;
        int brightness;
        int fade;
    public:
    Led();
    Led(int pin, int brightness);
    ~Led();
    void setBrightness(int brightness);
    int getBrightness() const;
    int getFade() const;
    int setFade(int fade);
    void setPin(int pin);
    int getPin() const;
};