import csv
import sys


def main():
    if len(sys.argv) != 3:
        raise Exception("Sorry give in the right amount of commands")
    databaseFileName = sys.argv[1]
    textFileName = sys.argv[2]

    sequences, subjects = loadcsv(databaseFileName)
    dna = loadTxt(textFileName)

    sequenceCounts = countSequences(sequences, subjects, dna)
    match = checkMatch(subjects, sequenceCounts)

    print(match)


def loadcsv(databaseFileName):
    with open(databaseFileName) as csvfile:
        reader = csv.reader(csvfile, delimiter=" ")
        sequences = []
        subjects = []
        for row in reader:
            newSubject = [int(x) if x.isdigit()
                          else x for x in ','.join(row).split(',')]
            subjects.append(newSubject)
        sequences = subjects[0][1:]
        subjects = subjects[1:]
        return sequences, subjects


def loadTxt(textFileName):
    with open(textFileName, 'r') as textfile:
        text = textfile.read().replace('\n', '')
    return text


def countSequences(sequences, subjects, dna):
    # longest sequences count for each sequence saved in this list
    sequenceCounts = [0] * (len(sequences))
    dnaSize = len(dna)
    for index, STR in enumerate(sequences):
        sequenceSize = len(STR)
        for i in range(dnaSize):
            sequenceSample = dna[i:i+sequenceSize]
            # if over limit break from loop
            if i+1+sequenceSize > dnaSize:
                break
            # if matched keep looking for matches
            if STR == sequenceSample:
                tmpSequenceCounts = 1
                while True:
                    endNext = i + (2 * sequenceSize)
                    startNext = i + sequenceSize
                    nextSequenceToCheck = dna[startNext:endNext]
                    if nextSequenceToCheck == STR:
                        i += sequenceSize
                        tmpSequenceCounts += 1
                    else:
                        if tmpSequenceCounts > sequenceCounts[index]:
                            sequenceCounts[index] = tmpSequenceCounts
                        break
    return sequenceCounts


def checkMatch(subjects, sequenceCounts):
    for subject in subjects:
        if subject[1:] == sequenceCounts:
            return subject[0]
    return "No match"


if __name__ == "__main__":
    main()
