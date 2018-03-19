void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void rotateRight()
{
}

void rotateLeft()
{
}

void execute()
{
}

void bigTing()
{
  char direction;
  float pos, dest;
  int decCount;
  switch (direction)
  {
    case 'N':
      {
        if (pos == 1.1)
        {
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 1.2)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 1.3)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 2.1)
        {
          if (dest == 1.1)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 2.2)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 2.3)
        {
          if (dest == 1.1)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 3.1)
        {
          if (dest == 1.1)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 3.2)
        {
          if (dest == 1.1)
          {
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 3.3)
        {
          if (dest == 1.1)
          {
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
      }
    case 'S':
      {
        if (pos = 1.1)
        {
          if (dest = 1.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos = 1.2)
        {
          if (dest = 1.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos = 1.3)
        {
          if (dest = 1.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos = 2.1)
        {
          if (dest = 1.1)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos = 2.2)
        {
          if (dest = 1.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos = 2.3)
        {
          if (dest = 1.1)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos = 3.1)
        {
          if (dest = 1.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos = 3.2)
        {
          if (dest = 1.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos = 3.3)
        {
          if (dest = 1.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 1.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 1.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 2.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 2.3)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest = 3.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest = 3.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
        }
      }
    case 'E':
      {
        if (pos == 1.1)
        {
          if (dest == 1.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 1.2)
        {
          if (dest == 1.1)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 1.3)
        {
          if (dest == 1.1)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 2.1)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 2.2)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 2.3)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 3.1)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 3.2)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 3.3)
        {
          if (dest == 1.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
      }
    case 'W':
      {
        if (pos == 1.1)
        {
          if (dest == 1.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 1.2)
        {
          if (dest == 1.1)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 1.3)
        {
          if (dest == 1.1)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 2.1)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 2.2)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 2.3)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateLeft();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 3.1)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
        }
        if (pos == 3.2)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.3)
          {
            rotateRight();
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
        }
        if (pos == 3.3)
        {
          if (dest == 1.1)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 1.2)
          {
            rotateRight();
            decCount = 2;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 1.3)
          {
            rotateRight();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.1)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 2.2)
          {
            rotateRight();
            decCount = 1;
            execute();
            rotateLeft();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 2.3)
          {
            rotateRight();
            decCount = 1;
            execute();
            //end of go
          }
          if (dest == 3.1)
          {
            decCount = 2;
            execute();
            //end of go
          }
          if (dest == 3.2)
          {
            decCount = 1;
            execute();
            //end of go
          }
        }
      }
  }
}
