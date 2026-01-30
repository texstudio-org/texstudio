#!/usr/bin/python3

# based on https://github.com/CSMathematics/CTAN-Packages-DataBase
# ported to python for easier maintenance


import requests
import json

# URLs to fetch JSON data from
urls = {
    "packages": "https://ctan.org/json/2.0/packages",
    "authors": "https://ctan.org/json/2.0/authors",
    "topics": "https://ctan.org/json/2.0/topics",
    "licenses": "https://ctan.org/json/2.0/licenses"
}

# Function to fetch JSON data from a URL
def fetch_json(url):
    response = requests.get(url)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return response.json()

# Fetch JSON data from all URLs
data = {key: fetch_json(url) for key, url in urls.items()}

# Create a dictionary for quick lookup of authors by ID
authors_dict = {author['key']: author for author in data["authors"]}

# Create a dictionary for quick lookup of topics by ID
topics_dict = {topic['key']: topic for topic in data["topics"]}

# Create a dictionary for quick lookup of topics by ID
license_dict = {license['key']: license for license in data["licenses"]}

# Process the packages data
fileName = f"packageDatabase.json"
packages = data["packages"]
package_content = []
c = 0
for package in packages:
    c += 1
    package_key = package['key']
    package_url = f"https://www.ctan.org/json/2.0/pkg/{package_key}"
    package_data = fetch_json(package_url)
    
    if 'authors' in package_data:
        authors = package_data['authors']
        package_data['authors'] = [authors_dict[a['id']] for a in authors]

    if 'topics' in package_data:
        topics = package_data['topics']
        package_data['topics'] = [topics_dict[a] for a in topics]

    if 'license' in package_data:
        licenses = package_data['license']
        if isinstance(licenses, list):
            package_data['license'] = [license_dict[a] for a in licenses]
        else:
            if licenses in license_dict:
                package_data['license'] = license_dict[licenses]
        

    print(f"Package: {package_key}")

    package_content.append(package_data)

# Save the processed data to a JSON file
print(f"writing {c} packages to file {fileName}...")
with open(fileName, "w") as file:
    json.dump(package_content, file, indent=2)

