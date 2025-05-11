int old_power = 0;
int target_power = 0;
int old_level = 0;
int target_level = 0;

void level_adjust(int old, int target);

struct DEV_DimmableLED : Service::LightBulb
{
  LedPin *ledPin;
  SpanCharacteristic *power;
  SpanCharacteristic *level;
  
  DEV_DimmableLED(int pin) : Service::LightBulb(){

    power=new Characteristic::On();     
                
    level=new Characteristic::Brightness(50);
    level->setRange(5,100,1);

    this->ledPin=new LedPin(pin);
    
  }

  boolean update()
  {
    target_power = power->getNewVal();
    target_level = level->getNewVal();
    
    if (target_power != old_power)
    {
      if (target_power == 0)
      {
        Serial.print("Turning off");
        level_adjust(target_level, 0);
      }
      else if (target_power == 1)
      {
        Serial.print("Turning on");
        level_adjust(0, target_level);
      }
    }

    if (target_level != old_level)
    {
      level_adjust(old_level, target_level);
    }

    old_power = target_power;
    old_level = target_level;


    Serial.print("Power: ");
    Serial.println(old_power);

    return(true);
  
  }

  void level_adjust(int level, int target)
  {
    if (level > target)
    {
      while (level != target)
      {
        level--;
        ledPin->set(level);
        delay(10);
      }
    }
    else if (level < target)
    {
      while (level != target)
      {
        level++;
        ledPin->set(level);
        delay(10);
      }
    }
    else
    {
      ledPin->set(level);
    }
  }

};

