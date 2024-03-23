class Robot:
    def __init__(self, x, y, direction):
        self.x = x
        self.y = y
        self.direction = direction


    def turnRight(self):
        if self.direction == 'north':
            self.direction = 'east'
        elif self.direction == 'south':
            self.direction = 'west'
        elif self.direction == 'east':
            self.direction = 'south'
        elif self.direction == 'west':
            self.direction = 'north'

    def turnLeft(self):
        if self.direction == 'north':
            self.direction = 'west'
        elif self.direction == 'south':
            self.direction = 'east'
        elif self.direction == 'east':
            self.direction = 'north'
        elif self.direction == 'west':
            self.direction = 'south'

    def advance(self):
        if self.direction == 'north':
            self.y += 1
        elif self.direction == 'south':
            self.y -= 1
        elif self.direction == 'east':
            self.x += 1
        elif self.direction == 'west':
            self.x -= 1

    def move(self, instructions):
        for instruction in instructions:
            if instruction =='R':
                self.turnRight()
            elif instruction =='L':
                self.turnLeft()
            elif instruction =='A':
                self.advance()
            else:
                raise ValueError("Wrong instructions")
        return True 

if __name__ == "__main__":
    while True:
        try:
            x = int(input("\nEnter start x: " ))
            y = int(input("Enter start y: " ))
            direction = input("Enter start direction: " )
            instructions = input("Enter instructions:" )
            if direction not in ['north', 'west', 'east', 'south']:
                raise ValueError("Wrong direction")
        
            robot = Robot(x, y, direction)
            if robot.move(instructions):
                print(f"Final position: {{X:{robot.x}, Y:{robot.y}}}, direction {robot.direction}")
        
        except ValueError as e:
                print(f"Error: {e}")
