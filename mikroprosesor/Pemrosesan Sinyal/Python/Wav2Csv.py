import sys, os, os.path
from scipy.io import wavfile
import pandas as pd

input_filename = "../Data/anti-aliasing-out.wav" # nama file input WAV, diganti jika file berbeda
output_filename = "../Data/anti-aliasing-out.csv" # nama output file CVS, diganti jika file berbeda

samrate, data = wavfile.read(str(input_filename))
print("Samrate = ", samrate)
print(' Load is Done! \n')


wavData = pd.DataFrame(data)

if len(wavData.columns) == 2:
    print('Stereo .wav file\n')
    wavData.columns = ['VIN', 'LPF_OUT']
    stereo_R = pd.DataFrame(wavData['VIN'])
    stereo_L = pd.DataFrame(wavData['LPF_OUT'])
    print('Saving...\n')
    #stereo_R.to_csv(str(input_filename[:-4] + "_Output_stereo_VIN.csv"), mode='w')
    #stereo_L.to_csv(str(input_filename[:-4] + "_Output_stereo_LPF_OUT.csv"), mode='w')
    wavData.to_csv(output_filename, mode='w')
    print('Save is done ' + str(input_filename[:-4]) + '_Output_stereo_RL.csv')

elif len(wavData.columns) == 1:
    print('Mono .wav file\n')
    wavData.columns = ['M']

    wavData.to_csv(output_filename, mode='w')

    print('Save is done ' + str(input_filename[:-4]) + '_Output_mono.csv')

else:
    print('Multi channel .wav file\n')
    print('number of channel : ' + len(wavData.columns) + '\n')
    wavData.to_csv(output_filename, mode='w')

    print('Save is done ' + str(input_filename[:-4]) + 'Output_multi_channel.csv')
    
# Ref : https://github.com/Lukious/wav-to-csv
