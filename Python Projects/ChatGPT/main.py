import torch
from gtts import gTTS
import os
from transformers import GPT2LMHeadModel, GPT2Tokenizer

tokenizer = GPT2Tokenizer.from_pretrained('gpt2')
model = GPT2LMHeadModel.from_pretrained('gpt2')

sequence = "What is the definition of Awsome?"

inputs = tokenizer.encode(sequence, return_tensors='pt')
outputs = model.generate(inputs, max_length=200, pad_token_id=tokenizer.eos_token_id, temperature=0.7)
text = tokenizer.decode(outputs[0], skip_special_tokens=True)

language = 'en'
obj = gTTS(text=text, lang=language, slow=False)
obj.save("welcome.mp3")
print(text)

# Play the audio file using the appropriate command for your OS
# For macOS:
os.system("afplay welcome.mp3")

# For Windows:
#os.system("start welcome.mp3")

# For Linux:
# os.system("mpg321 welcome.mp3")
