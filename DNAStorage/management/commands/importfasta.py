from django.core.management.base import BaseCommand
from DNAStorage.ProcessFasta import run


class Command(BaseCommand):
    args = ''
    help = 'Imports any fasta files that are in the DNAStorage/to_import folder'

    def handle(self, *args, **options):
        self.stdout.write("Processing all files in DNAStorage/to_import folder...\n")

        run()

        self.stdout.write("Done importing all present fasta files!\n")
        