#encoding=utf-8

from gensim import corpora,models,similarities
import jieba
import jieba.analyse
import logging

logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

CORPUS_FILE = 'comment_100000'
STOP_WORD_FILE = 'chinese_stop_words2.txt'


class MyCorpus(object):
    def __init__(self,corpus_file,corpus_dictionary):
        self.dictionary = corpus_dictionary
        self.corpus_file = corpus_file
    def __iter__(self):
        for line in open(self.corpus_file):
            yield self.dictionary.doc2bow(jieba.cut(line.strip()))


def generate_stop_ids(dictionary):
    stop_ids = []
    for stopword in open(STOP_WORD_FILE):
        try:
           stop_ids.append(dictionary.token2id[stopword.strip().decode('utf-8')])
        except KeyError:
           pass
    return stop_ids


def main():

    #dictionary = corpora.Dictionary(jieba.analyse.extract_tags(line.strip(),5) for line in open(CORPUS_FILE))
    dictionary = corpora.Dictionary(jieba.cut(line.strip()) for line in open(CORPUS_FILE))
   
    dictionary.filter_tokens(generate_stop_ids(dictionary))
    dictionary.compactify()

    corpus = MyCorpus(CORPUS_FILE,dictionary)

    model = models.LdaModel(corpus,id2word=dictionary, num_topics=10,update_every=1,chunksize=10000,passes=1)
    model.show_topics(10)


if __name__ == '__main__':
    main()
